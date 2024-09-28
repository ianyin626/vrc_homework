#include "devices.h"
#include "utilities.h"
#include "tasks.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
int route = 0;
bool continue_task = true;

void move(double left_speed, double right_speed) {
    left_speed *= 120;
    right_speed *= 120;
    leftFront.spin(directionType::fwd, left_speed, voltageUnits::mV);
    leftMiddle.spin(directionType::fwd, left_speed, voltageUnits::mV);
    leftBack.spin(directionType::fwd, left_speed, voltageUnits::mV);
    rightFront.spin(directionType::fwd, right_speed, voltageUnits::mV);
    rightMiddle.spin(directionType::fwd, right_speed, voltageUnits::mV);
    rightBack.spin(directionType::fwd, right_speed, voltageUnits::mV);
}

void split_arcade() {
    int32_t dead_band = 5;
    int32_t axis3_pos = getAxis3() * 0.8;
    int32_t axis1_pos = getAxis1() * 0.8;
    if (std::abs(axis3_pos) < dead_band) {
        axis3_pos = 0;
    }
    if (std::abs(axis1_pos) < dead_band) {
        axis1_pos = 0;
    }
    move((axis3_pos + axis1_pos), axis3_pos - axis1_pos);
}

double mod(double input, int base) {
    base = abs(base);
    double output = fmod(input, base);
    output = output > 0 ? output + base : base;
    return output;
}

double convert_inertial_angle(double current, double target, int turn_direction) {
    double converted_angle;
    double target_angle = mod(target, 360);
    double current_angle = mod(current, 360);
    double diff;

    if (turn_direction == 1)
    {
        diff = mod((target_angle - current_angle), 360);
        converted_angle = current + diff;
    } else {
        diff = mod((current_angle - target_angle), 360);
        converted_angle = current - diff;
    }
    return converted_angle;
}

double cap(double input, uint32_t max_value) {
    if (fabs(input) > max_value) {
        return (input >= 0) ? max_value : max_value * -1.0;
    }
    return input;
}

double getSign(double input) {
    if (input >= 0) {
        return 1;
    } else {
        return -1;
    }
}

void PID_turn(double target, double error_tolerance, double speed_tolerance) {
    double timer_start = getTimer();
    long delay = 10;
    double kp = 2.6;
    double ki = 0.07;
    double kd = 18;
    double porportional_correction = 0;
    double integral_correction = 0;
    double derivative_correction = 0;
    double current_heading = getInertial();
    double target_heading = target;
    double current_error = target_heading - current_heading;
    double past_error = current_error;
    double error_sum = 0;
    double total_correction = 0;
    double integral_range = 10;

    while(fabs(current_error) > error_tolerance || fabs(getGyroRate()) > speed_tolerance) {
        current_heading = getInertial();
        current_error = target_heading - current_heading;

        if (fabs(current_error) < integral_range) {
            error_sum = error_sum + current_error;
        } else {
            error_sum = 0;
        }
        if ((current_error * past_error) < 0) {
            error_sum = 0;
        }
        porportional_correction = current_error * kp;
        integral_correction = error_sum * ki;
        derivative_correction = getGyroRate() * -1 * kd;
        total_correction = porportional_correction + integral_correction + derivative_correction;

        if (fabs(total_correction) < MIN_DRIVE_SPEED && fabs(getGyroRate()) < speed_tolerance) {
            total_correction = getSign(total_correction) * MIN_DRIVE_SPEED;
        }
        
        move(total_correction, total_correction * -1);
        past_error = current_error;
        vexDelay(delay);
        logMessage("%.2f, %.2f, %.2f, %.2f", current_error, integral_correction, derivative_correction, total_correction);
    }
    move(0, 0);
    double timer_end = getTimer();
    logMessage("Time(ms): %.2f", timer_end - timer_start);
}

void PID_forward(double target, double error_tolerance, double speed_tolerance, double speedPercentage) {
    double startTime = Brain.timer(timeUnits::msec);
    long delay = 10;
    double kp = 4.0;
    double ki = 0.5;
    double kd = 30;
    double porportional_correction = 0;
    double integral_correction = 0;
    double derivative_correction = 0;
    rightFront.setPosition(0, rotationUnits::deg);
    double current_position = getPosition();
    double target_distance = target;
    double current_error = target_distance - current_position;
    double past_error = current_error;
    double error_sum = 0;
    double total_correction = 0;
    double integral_range = 3;
    double motorRate = getMotorRate();

    while (fabs(current_error) > error_tolerance || fabs(motorRate) > speed_tolerance) {
        current_position = getPosition();
        current_error = target - current_position;

        if (fabs(current_error) < integral_range) {
            error_sum = error_sum + current_error;
        } else {
            error_sum = 0;
        }
        if ((current_error * past_error) < 0) {
            error_sum = 0;
        }
        porportional_correction = current_error * kp;
        integral_correction = error_sum * ki;
        derivative_correction = motorRate * -1 * kd;
        total_correction = porportional_correction + integral_correction + derivative_correction;

        move(total_correction * speedPercentage, total_correction * speedPercentage);
        past_error = current_error;
        // logMessage("%.2f %.2f %.0f", current_error, getMotorRate(), total_correction);
        vexDelay(delay);
        motorRate = getMotorRate();
    }
    logMessage("PID forward %.3f", Brain.timer(timeUnits::msec) - startTime);
}

void PID_drift(double target_angle, double base_speed, double max_speed, double error_tolerance, double speed_tolerance) {
    long delay = 10;
    double kp = 1.4;
    double ki = 0.1;
    double kd = 20;
    double porportional_correction = 0;
    double integral_correction = 0;
    double derivative_correction = 0;
    double current_heading = getInertial();
    double target_heading = target_angle;
    double current_error = target_heading - current_heading;
    double past_error = current_error;
    double error_sum = 0;
    double total_correction = 0;
    double integral_range = 3;
    double gyroRate = getGyroRate();
    while (fabs(current_error) > error_tolerance || fabs(gyroRate) > speed_tolerance) {
        current_heading = getInertial();
        current_error = target_heading - current_heading;

        if (fabs(current_error) < integral_range) {
            error_sum = error_sum + current_error;
        } else {
            error_sum = 0;
        }
        if ((current_error * past_error) < 0) {
            error_sum = 0;
        }
        porportional_correction = current_error * kp;
        integral_correction = error_sum * ki;
        derivative_correction = gyroRate * -1 * kd;
        total_correction = cap((porportional_correction + integral_correction + derivative_correction), max_speed);
        
        move(base_speed + total_correction, base_speed - total_correction);
        past_error = current_error;
        logMessage("%.3f %.3f %.3f", gyroRate, current_error, total_correction);
        vexDelay(delay);
        gyroRate = getGyroRate();
    }
    move(-100, -100);
    vexDelay(25);
    move(0, 0);
    logMessage("Exit");
}

void encoderForward(double target, double speed) {
    double startPosition = getPosition();
    while(getSign(speed) * target > getSign(speed) * (getPosition() - startPosition)) {
        move(speed, speed);
        vexDelay(10);
    }
    logMessage("W(%.0f+%.0f+%.0f)/(%.0f+%.0f+%.0f)", leftFront.position(rotationUnits::deg), 
    leftMiddle.position(rotationUnits::deg), 
    leftBack.position(rotationUnits::deg), 
    rightFront.position(rotationUnits::deg), 
    rightMiddle.position(rotationUnits::deg), 
    rightBack.position(rotationUnits::deg));
    move(0, 0);
}

void intake(double volt) {
    upIntake.spin(directionType::fwd, volt * 100, voltageUnits::mV);
    roller.spin(directionType::fwd, volt * 120, voltageUnits::mV);
}

void intake_backward() {
    upIntake.spin(directionType::rev, 12000, voltageUnits::mV);
    roller.spin(directionType::rev, 12000, voltageUnits::mV);
}

bool intake_is_spinning = false;

void intake_toggle_forward() {
    if (intake_is_spinning == false) {
        intake(100);
        intake_is_spinning = true;
    } else {
        // upIntake.stop();
        // roller.stop();
        intake_is_spinning = false;
    }
 }

void intake_toggle_backward() {
    if (intake_is_spinning == false) {
        intake_backward();
        intake_is_spinning = true;
    } else {
        // upIntake.stop();
        // roller.stop();
        intake_is_spinning = false;
    }
}

bool cylinderOpen = false;
void cylinderControl() {
    if (!cylinderOpen) {
        mobileGoalHook.open();
        cylinderOpen = true;
    } else {
        mobileGoalHook.close();
        cylinderOpen = false;
    }
}

void initialize() {
    leftFront.resetPosition();
    leftMiddle.resetPosition();
    mobileGoalHook.close();
    opticalSensor.setLight(ledState::on);
}

void macro_actions() {
    while (true) {
        // // if (continue_task) {
        // if (Controller.ButtonR1.PRESSED) {
        //     intake_toggle_forward();
        // } else if (Controller.ButtonR2.PRESSED) {
        //     intake_toggle_backward();
        // }
        // // }
        vexDelay(10);
    }
}
void initialize_macros() {
    vex::thread task(macro_actions);
}