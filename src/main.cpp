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
    mobileGoalHook.open();
    expectedRingColor = 2;
    intake(100);
}

void liftTurnToPosition() {
    lift.setBrake(brakeType::hold);
    double error = targetLiftPosition - lift.position(rotationUnits::deg);
    double kp = 3;
    while (fabs(error) > 2)
    {
        lift.spin(directionType::fwd, error * kp, voltageUnits::volt);
        error = targetLiftPosition - lift.position(rotationUnits::deg);
        logMessage("%.0f", lift.position(rotationUnits::deg));
        vexDelay(10);
    }
    lift.setBrake(brakeType::brake);
    lift.spin(directionType::fwd, 0, voltageUnits::volt);
}

void autonomous(void) {
    switch (route) {
    case 0:
        leftFront.resetPosition();
        leftMiddle.resetPosition();
        leftBack.resetPosition();
        rightFront.resetPosition();
        rightMiddle.resetPosition();
        rightBack.resetPosition();
        autoSkills();
        break;
    
    case 1:
        mobileGoalHook.open();
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
    expectedRingColor = RING_COLOR_BLUE;
    Controller.Screen.print("ExpectedColor: %s", expectedRingColor == RING_COLOR_BLUE ? "blue": "red ");
    mobileGoalHook.close();
    // initialize_macros();
    // task taskIntake(intake_control);
    // task taskOptical(opticalControl);
    // task taskOptical2(intakeReverseOptical);
    // task taskDetectRingStatus(detectRingStatus);
    // task taskDetectRingLeave(detectRingLeave);
    while (true) {
        // Intake(both) control
        if (!jammed) {
            if (getControllerL1() && !getControllerL2()) {
                intake(100);
            } else if (!getControllerL1() && getControllerL2()) {
                intake(-100);
            } else {
                intake(0);
            }
        }

        // Lift control: A - Reset, B - Alliance Stake, X - Wall Stake
        if (getControllerButtonA()) {
            targetLiftPosition = 0;
            thread liftAction(liftTurnToPosition);
        } else if (getControllerButtonB()) {
            targetLiftPosition = 100;
            thread liftAction(liftTurnToPosition);
        } else if (getControllerButtonX()) {
            targetLiftPosition = 690;
            thread liftAction(liftTurnToPosition);
        }
        
        // Mobile goal hook control
        if (getControllerButtonR1()) {
            grabMobileGoal();
        } else if (getControllerButtonR2()) {
            dropMobileGoal();
        }

        split_arcade();

        // Switch expected ring color
        if (getControllerButtonY()) {
            expectedRingColor = expectedRingColor == RING_COLOR_BLUE ? RING_COLOR_RED: RING_COLOR_BLUE;
        }

        vexDelay(10);
    }
}

int main() {
    // task taskholdLift(holdLiftAnyPos);
    task taskDetectStatus(detectRobotStatus);
    task taskRouteSelect(autonRouteSelect);
    // unjam = true;
    // task taskUnjamming(unjamming);
    // task taskDropgoal(forward_drop_goal); // only used once
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    pre_auton();

    while (true)
    {
        wait(100, msec);
    }
}
