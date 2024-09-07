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
#include "autonomous.h"

using namespace vex;

competition Competition;

void pre_auton() {
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
    switch (route) {
    case 0:
        autohomework();
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
    // task taskDropgoal(forward_drop_goal); // only used once
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    pre_auton();

    while (true)
    {
        wait(100, msec);
    }
}
