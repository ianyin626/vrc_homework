/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Ian Yin                                                   */
/*    Created:      7/2/2024, 11:10:41 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "devices.h"
#include "basic_functions.h"
#include "tasks.h"
#include "utilities.h"

using namespace vex;

competition Competition;

void pre_auton() {
}

void auto_route_test() {
    PID_drift(180, 50, 100, 0.5, 0.1);
}

void auto15secgoal() {
    double startTime = Brain.timer(timeUnits::msec);
    encoderForward(-30, -100);
    encoderForward(-70, -30);
    Hook.open();
    encoderForward(-15, -40);
    PID_forward(10, 0.5, 0.15, 1);
    intake(100);
    PID_turn(-45, 0.75, 0.03);
    Hook.close();
    encoderForward(100, 70);
    PID_forward(30, 0.5, 0.15, 0.4);
    vexDelay(300);
    intake(0);
    PID_turn(110, 0.75, 0.02);
    PID_forward(170, 0.5, 0.15, 1);
}

void auto15secring2() {
    encoderForward(-30, -100);
    encoderForward(-70, -40);
    Hook.open();
    encoderForward(-15, -40);
    PID_forward(10, 0.5, 0.15, 1);
    intake(100);
    PID_turn(-90, 0.75, 0.15);
}

void auto15secring() {
    double startTime = Brain.timer(timeUnits::msec);
    encoderForward(-30, -100);
    encoderForward(-70, -40);
    Hook.open();
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
    Hook.close();
    PID_forward(30, 0.5, 0.15, 1);
    PID_forward(-40, 0.5, 0.15, 1);
    intake(0);
    PID_turn(180, 0.75, 0.02);
    encoderForward(-25, -100);
    encoderForward(50, 50);
    logMessage("time: %.0f", Brain.timer(timeUnits::msec) - startTime);
}

void presetThrowRing() {
    initialize();
    task taskDetectRingStatus(detectRingStatusUp);
    task taskDetectRingLeave(detectRingThrow);
    Hook.open();
    expectedRingColor = 2;
    intake(100);
}

void autonomous(void) {
    // auton15sec();
    switch (route) {
    case 0:
        auto15secring(); 
        break;
    
    case 1:
        Hook.open();
        presetThrowRing();
        break;
    
    case 2:
        break;
    
    case 3:
        break;
    
    case 4:
        break;
    
    case 5:
        break;
    
    case 6:
        break;
    
    case 7:
        break;
    }

    while (true) {
        vexDelay(10);
    }
}

void usercontrol(void) {
    expectedRingColor = 2;
    Controller.Screen.print("ExpectedColor: %s", expectedRingColor == 2 ? "blue": "red ");
    Hook.open();
    // initialize_macros();
    target = 1440;
    // task taskIntake(intake_control);
    // task taskOptical(opticalControl);
    // task taskOptical2(intakeReverseOptical);
    // task taskDetectRingStatus(detectRingStatus);
    // task taskDetectRingLeave(detectRingLeave);
    while (true) {
        if (!intakeReverse) {
            if (getControllerL1() && !getControllerL2() && !intakeStop) {
                intake(100);
                intakeReversing = false;
            } else if (getControllerL2() && !getControllerL1() && !intakeStop) {
                intake(-100);
                intakeReversing = true;
            } else if (!getControllerL1() && !getControllerL2()) {
                intake(0);
            } else {
                intake(0);
            }
        }
        split_arcade();
        if (getControllerButtonY()) {
            expectedRingColor = expectedRingColor == 2 ? 1: 2;
            Controller.Screen.clearLine(4);
            Controller.Screen.setCursor(4, 1);
            Controller.Screen.print("ExpectedColor: %s", expectedRingColor == 2 ? "blue": "red ");
        }
        vexDelay(10);
    }
    if (getControllerButtonX()) {
        Hook.open();
    }
}

int main() {
    task taskDetectStatus(detectRobotStatus);
    task taskRouteSelect(autonRouteSelect);
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    pre_auton();

    while (true)
    {
        wait(100, msec);
    }
}
