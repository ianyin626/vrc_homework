#include "devices.h"
#include "v5.h"
#include "v5_vcs.h"
#include <math.h>
#include <iostream>

using namespace vex;
extern brain Brain;
extern controller Controller;
extern motor leftFront;
extern motor leftMiddle;
extern motor leftBack;
extern motor rightFront;
extern motor rightMiddle;
extern motor rightBack;
extern motor leftIntake;
extern motor rightIntake;
extern inertial Inertial;

double initial_heading = 0;

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
    int dead_band = 5;
    int axis3_pos;
    int axis1_pos;
    axis3_pos = get_axis3;
    axis1_pos = get_axis1;
    if (abs(axis3_pos) < dead_band) {
        axis3_pos = 0;
    }
    if (abs(axis1_pos) < dead_band) {
        axis1_pos = 0;
    }
    move(axis3_pos + axis1_pos, axis3_pos - axis1_pos);
    // printf("%d %d\n", axis3_pos, axis1_pos);
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
    double timer_start = get_timer;
    long delay = 10;
    double kp = 2;
    double ki = 0.4;
    double kd = 15;
    double porportional_correction = 0;
    double integral_correction = 0;
    double derivative_correction = 0;
    double current_heading = get_inertial;
    double target_heading = target;
    double current_error = target_heading - current_heading;
    double past_error = current_error;
    double error_sum = 0;
    double total_correction = 0;
    double integral_range = 10;

    while(fabs(current_error) > error_tolerance || fabs(get_gyroRate) > speed_tolerance) {
        current_heading = get_inertial;
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
        derivative_correction = get_gyroRate * -1 * kd;
        total_correction = porportional_correction + integral_correction + derivative_correction;
        
        move(total_correction, total_correction * -1);
        past_error = current_error;
        vexDelay(delay);
        printf("%f %f %f %f\n", current_error, current_heading, total_correction, get_gyroRate);
    }
    printf("Final: current_error %f, current_heading %f, total_correction %f\n", 
    current_error, current_heading, total_correction);
    move(0, 0);
    double timer_end = get_timer;
    printf("Time(ms): %f\n", timer_end - timer_start);
    Brain.Screen.print("PID Turn End\n");
}

void PID_forward(double target, double error_tolerance, double speed_tolerance) {
    Brain.Screen.print("PID_forward starting/n");
    double timer_start = get_timer;
    long delay = 10;
    double kp = 3.2;
    double ki = 0.1;
    double kd = 18;
    double porportional_correction = 0;
    double integral_correction = 0;
    double derivative_correction = 0;
    leftFront.resetPosition();
    leftMiddle.resetPosition();
    double current_position = get_position;
    double target_distance = target;
    double current_error = target_distance - current_position;
    double past_error = current_error;
    double error_sum = 0;
    double total_correction = 0;
    double integral_range = 5;

    while (fabs(current_error) > error_tolerance || fabs(get_motorRate) > speed_tolerance) {
        current_position = get_position;
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
        derivative_correction = get_motorRate * -1 * kd;
        total_correction = porportional_correction + integral_correction + derivative_correction;

        move(total_correction, total_correction);
        past_error = current_error;
        // printf("%f %f %f %f\n", porportional_correction, integral_correction, derivative_correction, get_motorRate);
        std::cout << porportional_correction  <<  ", " <<  integral_correction  <<  ", " << derivative_correction <<  ", " << get_motorRate <<  std::endl;
        vexDelay(delay);
    }
    move(0, 0);
    printf("PID forward\n");
}   

void PID_drift(double target_angle, double base_speed, double max_speed, double error_tolerance, double speed_tolerance) {
    long delay = 10;
    double kp = 1.4;
    double ki = 0.1;
    double kd = 25;
    double porportional_correction = 0;
    double integral_correction = 0;
    double derivative_correction = 0;
    double current_heading = get_inertial;
    double target_heading = target_angle;
    double current_error = target_heading - current_heading;
    double past_error = current_error;
    double error_sum = 0;
    double total_correction = 0;
    double integral_range = 10;
    while (fabs(current_error) > error_tolerance || fabs(get_gyroRate) > speed_tolerance) {
        current_heading = get_inertial;
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
        derivative_correction = get_gyroRate * -1 * kd;
        total_correction = cap((porportional_correction + integral_correction + derivative_correction), max_speed);
        
        move(base_speed + total_correction, base_speed - total_correction);
        past_error = current_error;
        vexDelay(delay);
        printf("%f %f\n", get_gyroRate, current_error);
    }
    move(0, 0);
}

void intake_forward() {
    rightIntake.spin(directionType::fwd, 12700, voltageUnits::mV);
    leftIntake.spin(directionType::fwd, 12700, voltageUnits::mV);
}

void intake_backward() {
    rightIntake.spin(directionType::rev, 12700, voltageUnits::mV);
    leftIntake.spin(directionType::rev, 12700, voltageUnits::mV);
}

bool intake_is_spinning = false;

void intake_toggle_forward() {
    if (intake_is_spinning == false) {
        intake_forward();
        intake_is_spinning = true;
    } else {
        rightIntake.stop();
        leftIntake.stop();
        intake_is_spinning = false;
    }
 }

void intake_toggle_backward() {
    if (intake_is_spinning == false) {
        intake_backward();
        intake_is_spinning = true;
    } else {
        rightIntake.stop();
        leftIntake.stop();
        intake_is_spinning = false;
    }
}

void intake_stop() {
    rightIntake.stop();
    leftIntake.stop();
}

void initialize() {
    Inertial.calibrate();
    vexDelay(5000);
    double timer_end = get_timer;
}

void macro_actions() {
    while (1) {
        // if (Controller.ButtonL1.PRESSED) {
        //     std::cout << "Controller.ButtonL1.PRESSED" << std::endl;
        //     intake_forward(); // Note: untested
        // } else {
        //     std::cout << "Controller.ButtonL1.RELEASED" << std::endl;
        //     intake_stop(); // Note: untested
        // }
        Controller.ButtonL1.pressed(intake_forward);
        Controller.ButtonL1.released(intake_stop);
        Controller.ButtonL2.pressed(intake_backward);
        Controller.ButtonL2.released(intake_stop);
        if (Controller.ButtonR1.PRESSED) {
            intake_toggle_forward(); // Note:untested
        } else if (Controller.ButtonR2.PRESSED) {
            intake_toggle_backward(); // Note:untested
        }
        vexDelay(10);
    }
}
void initialize_macros() {
    vex::thread task(macro_actions);
}