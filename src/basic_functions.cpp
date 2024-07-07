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

void stop_all_motors() {
    move(0, 0);
}

void split_arcade() {
    int dead_band = 5;
    int axis3_pos;
    int axis1_pos;
    while(1) {
        axis3_pos = Controller.Axis3.position(percentUnits::pct);
        axis1_pos = Controller.Axis1.position(percentUnits::pct);
        if (abs(axis3_pos) < dead_band) {
            axis3_pos = 0;
        }
        if (abs(axis1_pos) < dead_band) {
            axis1_pos = 0;
        }
        move(axis3_pos + axis1_pos, axis3_pos - axis1_pos);
        vexDelay(10);
    }
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
    long delay = 10;
    double kp = 2;
    double ki = 0.4;
    double kd = 15;
    double porportional_correction = 0;
    double integral_correction = 0;
    double derivative_correction = 0;
    double current_heading = Inertial.rotation(rotationUnits::deg);
    double target_heading = target;
    double current_error = target_heading - current_heading;
    double past_error = target_heading - current_heading;
    double error_sum = 0;
    double total_correction = 0;
    double integral_range = 10;

    while(fabs(current_error) > error_tolerance || (fabs(Inertial.gyroRate(zaxis, dps)) / 100) > speed_tolerance) {
        current_heading = Inertial.rotation(rotationUnits::deg);
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
        derivative_correction = ((Inertial.gyroRate(zaxis, dps)) / 100) * -1 * kd;
        total_correction = porportional_correction + integral_correction + derivative_correction;
        // if (fabs(total_correction) < 1) {
        //     total_correction = total_correction > 0 ? 1 : -1;
        // }
        
        move(total_correction, total_correction * -1);
        past_error = current_error;
        vexDelay(delay);
        printf("%f %f %f %f\n", current_error, current_heading, total_correction, (Inertial.gyroRate(zaxis, dps)) / 100);
    }
    printf("Final: current_error %f, current_heading %f, total_correction %f\n", current_error, current_heading, total_correction);
    move(0, 0);
}