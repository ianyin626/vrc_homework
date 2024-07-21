#include "devices.h"
#include "utilities.h"
#include "tasks.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
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
    int32_t axis3_pos = getAxis3();
    int32_t axis1_pos = getAxis1();
    if (std::abs(axis3_pos) < dead_band) {
        axis3_pos = 0;
    }
    if (std::abs(axis1_pos) < dead_band) {
        axis1_pos = 0;
    }
    move(axis3_pos + axis1_pos, axis3_pos - axis1_pos);
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

void PID_turn(double target, double error_tolerance, double speed_tolerance) {
    Brain.Screen.print("PID Turn Start\n");
    double timer_start = getTimer();
    long delay = 10;
    double kp = 2;
    double ki = 0.2;
    double kd = 15;
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
        
        move(total_correction, total_correction * -1);
        past_error = current_error;
        vexDelay(delay);
        logMessage("%.3f %.3f %.3f %.3f", current_error, current_heading, total_correction, getGyroRate());
    }
    logMessage("Final: current_error %.3f, current_heading %.3f, total_correction %.3f", 
    current_error, current_heading, total_correction);
    move(0, 0);
    double timer_end = getTimer();
    logMessage("Time(ms): %.2f", timer_end - timer_start);
    Brain.Screen.print("PID Turn End\n");
}

void PID_forward(double target, double error_tolerance, double speed_tolerance) {
    Brain.Screen.print("PID_forward starting/n");
    long delay = 10;
    double kp = 3.2;
    double ki = 0.1;
    double kd = 25;
    double porportional_correction = 0;
    double integral_correction = 0;
    double derivative_correction = 0;
    double current_position = getPosition();
    double target_distance = target;
    double current_error = target_distance - current_position;
    double past_error = current_error;
    double error_sum = 0;
    double total_correction = 0;
    double integral_range = 5;
    double motorRate = getMotorRate();

    while (fabs(current_error) > error_tolerance || fabs(motorRate) > speed_tolerance) {
        current_position = getPosition();
        current_error = target_distance - current_position;

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

        move(total_correction, total_correction);
        past_error = current_error;
        logMessage("%.3f %.3f %.3f %.3f", current_error, error_sum, motorRate, total_correction);
        vexDelay(delay);
        motorRate = getMotorRate();
    }
    move(0, 0);
    logMessage("PID forward");
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



void intake(double volt) {
    forwardIntake.spin(directionType::fwd, volt * 120, voltageUnits::mV);
    backwardIntake.spin(directionType::fwd, volt * 120, voltageUnits::mV);
}

void intake_backward() {
    forwardIntake.spin(directionType::rev, 12000, voltageUnits::mV);
    backwardIntake.spin(directionType::rev, 12000, voltageUnits::mV);
}

bool intake_is_spinning = false;

void intake_toggle_forward() {
    if (intake_is_spinning == false) {
        intake(100);
        intake_is_spinning = true;
    } else {
        forwardIntake.stop();
        backwardIntake.stop();
        intake_is_spinning = false;
    }
 }

void intake_toggle_backward() {
    if (intake_is_spinning == false) {
        intake_backward();
        intake_is_spinning = true;
    } else {
        forwardIntake.stop();
        backwardIntake.stop();
        intake_is_spinning = false;
    }
}

void intake_stop() {
    forwardIntake.stop();
    backwardIntake.stop();
}

void initialize() {
    Inertial.calibrate();
    vexDelay(5000);

    leftFront.resetPosition();
    leftMiddle.resetPosition();
}

void macro_actions() {
    while (1) {
        if (continue_task) {
            if (Controller.ButtonX.PRESSED) {
                puncher_move = false;
                puncher.spinTo(2160, rotationUnits::deg, 100, velocityUnits::pct, true);
                puncher.setPosition(0, rotationUnits::deg);
                puncher_move = true;
            }

            if (Controller.ButtonL1.pressing()) {
                intake(100);
            } else if (Controller.ButtonL2.pressing()) {
                intake(-100);
            } else {
                intake(0);
            }
            if (Controller.ButtonR1.PRESSED) {
                intake_toggle_forward();
            } else if (Controller.ButtonR2.PRESSED) {
                intake_toggle_backward();
            }
        }
        vexDelay(10);
    }
}
void initialize_macros() {
    vex::thread task(macro_actions);
}