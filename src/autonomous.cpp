#include "autonomous.h"
#include "basic_functions.h"
#include "devices.h"
#include "utilities.h"
#include "tasks.h"


void auton15goalblue() {
    PID_forward(-87, 0.5, 0.15, 0.8);
    PID_turn(40, 0.75, 0.02);
    encoderForward(-25, -20);
    vexDelay(250);
    mobileGoalHook.open();
    intake(100);
    vexDelay(1200);
    PID_turn(-15, 0.75, 0.02);
    PID_forward(20, 0.5, 0.15, 0.7);
    vexDelay(500);
    intake(0);
    mobileGoalHook.close();
    vexDelay(250);
    PID_forward(23, 0.5, 0.15, 0.8);
    PID_turn(90, 0.75, 0.02);
    encoderForward(-40, -60);
    vexDelay(200);
    mobileGoalHook.open();
    intake(100);
    PID_forward(-7, 0.5, 0.15, 0.7);
    PID_turn(-30, 0.75, 0.02);
    PID_forward(42, 0.5, 0.15, 1);
}

void auton15ringblue() {
    lift.spinTo(45, rotationUnits::deg, 100, velocityUnits::pct, false);
    double startTime = Brain.timer(timeUnits::msec);
    encoderForward(-20, -100);
    encoderForward(-40, -40);
    grabMobileGoal();
    vexDelay(1000);
    PID_turn(90, 0.75, 0.02);
    spin_hook(100);
    spin_roller(100);
    PID_forward(50, 0.5, 0.1, 1);
    vexDelay(1000);
    PID_turn(-2, 0.75, 0.02);
    PID_forward(30, 0.5, 0.1, 1);
    vexDelay(300);
    PID_forward(-30, 0.5, 0.1, 1);
    PID_turn(25, 0.75, 0.02);
    PID_forward(35, 0.5, 0.1, 1);
    vexDelay(200);
    PID_forward(-35, 0.5, 0.1, 1);
    vexDelay(1000);
    PID_turn(-90, 0.75, 0.02);
    move(35, 35);
    vexDelay(2000);
    spin_hook(0);
    spin_roller(0);
    move(15, 15);
    vexDelay(1000);
    dropMobileGoal();
    move(0, 0);
    logMessage("time: %.0f", Brain.timer(timeUnits::msec) - startTime);
}

void auton15goalblue2() { // not usable
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

void firstQuarterSkills() {
    logMessage("First Part");
    dropMobileGoal();
    lift.spinTo(100, rotationUnits::deg, 100, velocityUnits::pct, true);
    double startTime = Brain.timer(timeUnits::msec);
    spin_hook(85); // 85 is the speed to make sure the rings dont fly out
    vexDelay(500);
    lift.spinTo(30, rotationUnits::deg, -100, velocityUnits::pct, false);
    PID_forward(32, 0.5, 0.1, 1);
    PID_turn(93, 0.75, 0.02);
    PID_forward(-35, 0.5, 0.1, 1);
    encoderForward(-13, -40);
    grabMobileGoal();
    vexDelay(500);
    PID_turn(3, 0.75, 0.02);
    spin_roller(100);
    PID_forward(55, 0.5, 0.5, 0.5);
    PID_turn(-87, 0.75, 0.02);
    vexDelay(250);
    PID_forward(55, 0.5, 0.1, 0.7);
    vexDelay(500);
    PID_turn(-175, 0.75, 0.02);
    PID_forward(50, 0.5, 0.1, 1);
    vexDelay(500);
    PID_forward(30, 0.5, 0.1, 1);
    vexDelay(750);
    PID_forward(-63, 0.5, 0.1, 1);
    PID_turn(-130, 0.75, 0.02);
    PID_forward(40, 0.5, 0.1, 1);
    vexDelay(1000);
    PID_turn(20, 0.75, 0.02);
    mobileGoalHook.close();
    move(-60, -60);
    vexDelay(1000);
    move(0, 0);
    PID_forward(35, 0.5, 0.1, 1);
    PID_turn(2, 0.75, 0.02);
    PID_forward(115, 0.5, 0.1, 1);
    spin_hook(0);
    PID_turn(90, 0.75, 0.02);
    move(-50, -50);
    vexDelay(500);
    move(0, 0);
    lift.spinTo(680, rotationUnits::deg, 100, velocityUnits::pct, true);
    spin_hook(85); // 85 is the speed to make sure the rings dont fly out
    vexDelay(1000);
    lift.spinTo(0, rotationUnits::deg, -100, velocityUnits::pct, true);
    logMessage("time: %.0f", Brain.timer(timeUnits::msec) - startTime);
}

void secondQuarterSkills() {
    Inertial.setRotation(90, rotationUnits::deg);
    Inertial.setHeading(90, rotationUnits::deg);
    lift.spinTo(30, rotationUnits::deg, 100, velocityUnits::pct, true);
    logMessage("Second Part");
    spin_hook(100);
    spin_roller(100);
    PID_forward(40, 0.5, 0.1, 1);
    PID_turn(0, 0.75, 0.02);
    PID_forward(60, 0.5, 0.1, 1);
    spin_hook(0);
    PID_turn(210, 0.75, 0.02);
    encoderForward(-90, -50);
    grabMobileGoal();
    encoderForward(-10, -40);
    PID_turn(110, 0.75, 0.02);
    dropMobileGoal();
    move(-100, -100);
    vexDelay(1000);
    move(0, 0);
    PID_forward(60, 0.5, 0.1, 1);
    lift.spinTo(100, rotationUnits::deg, 100, velocityUnits::pct, false);
    PID_turn(-120, 0.75, 0.02);
    move(-50, -50);
    while((Inertial.rotation() - -120) > -10) {
        double output = Inertial.rotation() - -120;
        logMessage("output: %.1f", output);
        move(-50 - output, -60 + output);
        vexDelay(10);
    }
    move(0, 0);
}

void autoSkills() {
    lift.resetPosition();
    // firstQuarterSkills();
    secondQuarterSkills();
}