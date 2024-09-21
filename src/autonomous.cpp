#include "autonomous.h"
#include "basic_functions.h"
#include "devices.h"
#include "utilities.h"
#include "tasks.h"


void auton15goal() {
    PID_forward(-93, 0.5, 0.15, 0.8);
    PID_turn(-40, 0.75, 0.02);
    encoderForward(-13, -20);
    vexDelay(250);
    mobileGoalHook.open();
    intake(100);
    PID_turn(20, 0.75, 0.02);
    vexDelay(300);
    PID_forward(20, 0.5, 0.15, 0.7);
    mobileGoalHook.close();
    PID_forward(30, 0.5, 0.15, 0.8);
    vexDelay(300);
    intake(0);
    encoderForward(-10, 40);
    PID_turn(90, 0.75, 0.02);
    encoderForward(-40, -60);
    vexDelay(200);
    mobileGoalHook.open();
    PID_forward(-7, 0.5, 0.15, 0.7);
    vexDelay(100);
    PID_turn(-30, 0.75, 0.02);
}

void auto_route_test() {
PID_forward(60, 0.5, 0.15, 1);
}

void auto15ring() {
    double startTime = Brain.timer(timeUnits::msec);
    encoderForward(-20, -100);
    encoderForward(-60, -40);
    grabMobileGoal();
    encoderForward(-10, -40);
    PID_forward(7, 0.5, 0.15, 1);
    intake(100);
    PID_turn(-135, 0.75, 0.03);
    PID_forward(50, 0.5, 0.15, 1);
    vexDelay(100);
    PID_forward(-2, 0.5, 0.15, 1);
    PID_turn(-110, 0.75, 0.02);
    PID_forward(30, 0.5, 0.15, 1);
    vexDelay(300); 
    PID_forward(-20, 0.5, 0.15, 1);
    PID_turn(-15, 0.75, 0.02);
    PID_forward(40, 0.5, 0.15, 1);
    vexDelay(200);
    PID_turn(60, 0.75, 0.02);
    encoderForward(100, 85);
    intake(30);
    PID_forward(17, 0.5, 0.15, 0.9);
    intake(0);
    PID_turn(100, 0.75, 0.02);
    intake(-100);
    PID_forward(15, 0.5, 0.15, 1);
    vexDelay(300);
    PID_forward(-20, 0.5, 0.15, 1);
    intake(100);
    PID_turn(60, 0.75, 0.02);
    PID_forward(40, 0.6, 0.15, 1);
    PID_turn(180, 0.75, 0.02);
    encoderForward(40, 50);
    dropMobileGoal();
    logMessage("time: %.0f", Brain.timer(timeUnits::msec) - startTime);
}

void auto15ring2() { // not usable
    double startTime = Brain.timer(timeUnits::msec);
    encoderForward(-30, -100);
    encoderForward(-70, -40);
    mobileGoalHook.open();
    encoderForward(-15, -40);
    PID_forward(10, 0.5, 0.15, 1);
    intake(100);
    PID_turn(-90, 0.75, 0.03);
    PID_forward(60, 0.5, 0.15, 1);
    PID_turn(-181, 0.75, 0.02);
    encoderForward(15, 75);
    PID_forward(27, 0.5, 0.15, 1); // keeps moving slowly when robot is intaking ring
    vexDelay(300);
    PID_forward(-25, 0.5, 0.15, 1);
    PID_turn(-200, 0.75, 0.02);
    PID_forward(-20, 0.5, 0.15, 1);
    PID_turn(-161, 0.75, 0.02);
    encoderForward(8, 70);
    PID_forward(30, 0.5, 0.15, 1);
    vexDelay(300);
    PID_forward(-45, 0.5, 0.15, 1);
    intake(40);
    PID_turn(60, 0.75, 0.2);
    intake(100);
    PID_forward(160, 0.5, 0.15, 1);
    mobileGoalHook.close();
    PID_forward(30, 0.5, 0.15, 1);
    PID_forward(-40, 0.5, 0.15, 1);
    intake(0);
    PID_turn(180, 0.75, 0.02);
    encoderForward(-25, -100);
    encoderForward(50, 50);
    logMessage("time: %.0f", Brain.timer(timeUnits::msec) - startTime);
}