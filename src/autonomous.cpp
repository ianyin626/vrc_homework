#include "autonomous.h"
#include "basic_functions.h"
#include "devices.h"
#include "utilities.h"
#include "tasks.h"


void auto15_goal_blue() {
    lift.spinTo(30, rotationUnits::deg, 100, velocityUnits::pct, false);
    double startTime = Brain.timer(timeUnits::msec);
    PID_forward(-28, 0.5, 0.1, 1);
    PID_turn(30, 0.75, 0.02);
    encoderForward(-35, -30);
    vexDelay(750);
    grabMobileGoal();
    vexDelay(250);
    PID_turn(90, 0.75, 0.02);
    spin_hook(100);
    spin_roller(100);
    vexDelay(1000);
    PID_forward(60, 0.5, 0.1, 1);
    vexDelay(1000);
    PID_turn(-90, 0.75, 0.02);
    move(50, 50);
    vexDelay(1500);
    move(10, 10);
    vexDelay(500);
    move(0, 0);
    dropMobileGoal();
    intake(0);
    logMessage("time: %.0f", Brain.timer(timeUnits::msec) - startTime);
}

void auto15_goal_red() {
lift.spinTo(30, rotationUnits::deg, 100, velocityUnits::pct, false);
    double startTime = Brain.timer(timeUnits::msec);
    PID_forward(-28, 0.5, 0.1, 1);
    PID_turn(-30, 0.75, 0.02);
    encoderForward(-35, -30);
    vexDelay(750);
    grabMobileGoal();
    vexDelay(250);
    PID_turn(-90, 0.75, 0.02);
    spin_hook(100);
    spin_roller(100);
    vexDelay(1000);
    PID_forward(60, 0.5, 0.1, 1);
    vexDelay(1000);
    PID_turn(90, 0.75, 0.02);
    move(50, 50);
    vexDelay(1500);
    move(10, 10);
    vexDelay(500);
    move(0, 0);
    dropMobileGoal();
    intake(0);
    logMessage("time: %.0f", Brain.timer(timeUnits::msec) - startTime);
}

void auton15ringred() {
    lift.spinTo(45, rotationUnits::deg, 100, velocityUnits::pct, false);
    double startTime = Brain.timer(timeUnits::msec);
    encoderForward(-20, -100);
    encoderForward(-35, -40);
    vexDelay(500);
    grabMobileGoal();
    vexDelay(1000);
    PID_turn(-90, 0.75, 0.02);
    spin_hook(100);
    spin_roller(100);
    PID_forward(50, 0.5, 0.1, 1);
    vexDelay(1000);
    PID_turn(2, 0.75, 0.02);
    PID_forward(30, 0.5, 0.1, 1);
    vexDelay(300);
    PID_forward(-30, 0.5, 0.1, 1);
    PID_turn(-25, 0.75, 0.02);
    PID_forward(35, 0.5, 0.1, 1);
    vexDelay(200);
    PID_forward(-35, 0.5, 0.1, 1);
    vexDelay(1000);
    PID_turn(90, 0.75, 0.02);
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

void firstQuarterSkills() {
    double startTime = Brain.timer(timeUnits::msec);
    logMessage("First Part");
    dropMobileGoal();
    lift.spinTo(100, rotationUnits::deg, 100, velocityUnits::pct, true);
    spin_hook(100);
    vexDelay(500);
    lift.spinTo(45, rotationUnits::deg, -100, velocityUnits::pct, false);
    PID_forward(40, 0.5, 0.1, 1);
    PID_turn(90, 0.75, 0.02);
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
    PID_turn(-145, 0.75, 0.02);
    PID_forward(40, 0.5, 0.1, 1);
    vexDelay(1000);
    PID_turn(20, 0.75, 0.02);
    mobileGoalHook.close();
    move(-60, -60);
    vexDelay(1000);
    move(0, 0);
    PID_forward(35, 0.5, 0.1, 1);
    PID_turn(-3, 0.75, 0.02);
    PID_forward(115, 0.5, 0.1, 1);
    spin_hook(0);
    PID_turn(90, 0.75, 0.02);
    move(-50, -50);
    vexDelay(500);
    move(0, 0);
    lift.setBrake(brakeType::hold);
    lift.spinTo(690, rotationUnits::deg, 100, velocityUnits::pct, true);
    lift.setBrake(brakeType::brake);
    spin_hook(100);
    vexDelay(1000);
    logMessage("time: %.0f", Brain.timer(timeUnits::msec) - startTime);
}

void secondQuarterSkills() {
    Inertial.setRotation(90, rotationUnits::deg);
    Inertial.setHeading(90, rotationUnits::deg);
    logMessage("Second Part");
    spin_hook(100);
    spin_roller(100);
    PID_forward(40, 0.5, 0.1, 1);
    lift.spinTo(30, rotationUnits::deg, -100, velocityUnits::pct, true);
    PID_turn(0, 0.75, 0.02);
    PID_forward(60, 0.5, 0.1, 1);
    spin_hook(0);
    PID_turn(215, 0.75, 0.02);
    encoderForward(-100, -40);
    grabMobileGoal();
    vexDelay(500);
    PID_turn(120, 0.75, 0.02);
    dropMobileGoal();
    move(-50, -50);
    vexDelay(1500);
    move(0, 0);
    PID_forward(70, 0.5, 0.1, 1);
    lift.spinTo(100, rotationUnits::deg, 100, velocityUnits::pct, false);
    PID_turn(-120, 0.75, 0.02);
    move(-35, -35);
    while((Inertial.rotation() - -120) > -5) {
        double output = Inertial.rotation() - -120;
        move(-50 - output, -60 + output);
        vexDelay(10);
    }
    stopDriving();
    vexDelay(300);
    PID_turn(-180, 0.75, 0.02);
    move(-50, -50);
    vexDelay(750);
    stopDriving();
    lift.spinTo(100, rotationUnits::deg, 100, velocityUnits::pct, true);
    spin_hook(100);
    spin_roller(100);
    vexDelay(750);
    spin_roller(0);
    spin_hook(0);
}

void thirdQuarterSkills() {
    Inertial.setRotation(-180, rotationUnits::deg);
    Inertial.setHeading(-180, rotationUnits::deg);
    logMessage("Third Part");
    PID_forward(10, 0.5, 0.1, 1);
    PID_turn(-95, 0.75, 0.02);
    encoderForward(-60, -50);
    vexDelay(500);
    grabMobileGoal();
    PID_turn(-110, 0.75, 0.02);
    dropMobileGoal();
    move(-50, -50);
    vexDelay(1500);
    move(0, 0);
    PID_turn(-90, 0.75, 0.02);
    PID_forward(90, 0.5, 0.1, 1);
    PID_turn(45, 0.75, 0.02);
    encoderForward(-35, -50);
    vexDelay(500);
    grabMobileGoal();
    spin_hook(100);
    spin_roller(100);
    vexDelay(300);
    PID_turn(130, 0.75, 0.02);
    PID_forward(75, 0.5, 0.1, 1);
    PID_turn(90, 0.75, 0.02);
    PID_forward(90, 0.5, 0.1, 1);
    vexDelay(750);
    dropMobileGoal();
    PID_turn(180, 0.75, 0.02);
    PID_forward(50, 0.5, 0.1, 1);
    vexDelay(150);
    spin_hook(0);
    spin_roller(0);
    PID_forward(-85, 0.5, 0.1, 1);
    PID_turn(-30, 0.75, 0.02);
    move(-35, -35);
    while((Inertial.rotation(rotationUnits::deg) - -30) > -5) {
        double output = Inertial.rotation() - -30;
        move(-50 - output, -60 + output);
        vexDelay(10);
    }
    stopDriving();
    vexDelay(300);
    PID_turn(-90, 0.75, 0.02);
    move(-50, -50);
    vexDelay(500);
    move(0, 0);
    lift.setBrake(brakeType::hold);
    lift.spinTo(690, rotationUnits::deg, 100, velocityUnits::pct, true);
    lift.setBrake(brakeType::brake);
    spin_hook(100);
    vexDelay(1000);
    spin_hook(0);
    spin_roller(0);
}

void autoSkills() {
    lift.resetPosition();
    lift.spinTo(30, rotationUnits::deg, 100, velocityUnits::pct, true); // not supposed ot exist
    // firstQuarterSkills();
    // secondQuarterSkills();
    thirdQuarterSkills();
    // lastQuarterSkills();
}