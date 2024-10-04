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

void auton_route_test() {
    PID_drift(180, 50, 100, 0.5, 0.1);
}

void auton15sec() {
    encoderForward(-40, -100);
    encoderForward(-60, -30);
    Hook.open();
    encoderForward(-10, -30);
    PID_forward(15, 0.5, 0.15, 0.8);
    intake(100);
    PID_turn(-100, 0.75, 0.03);
    PID_forward(60, 0.5, 0.15, 1);
    PID_turn(-180, 0.75, 0.02);
    encoderForward(15, 65);
    encoderForward(10, 20); // keeps moving slowly when robot is intaking ring
    vexDelay(1000);
    PID_forward(-30, 0.5, 0.15, 1);
    PID_turn(-160, 0.75, 0.02);
    encoderForward(15, 60);
    encoderForward(20, 20);
    vexDelay(300);
    PID_forward(-40, 0.5, 0.15, 1);
    PID_turn(0, 0.75, 0.2);
    PID_forward(85, 0.05, 0.15, 1);
    PID_turn(90, 0.75, 0.02);
    Hook.close();
    encoderForward(50, 70);
    PID_forward(120, 0.5, 0.15, 0.4);
    vexDelay(1000);
    intake(0);
    PID_forward(-50, 0.5, 0.15, 0.6);
    PID_turn(180, 0.75, 0.02);
    encoderForward(50, 40);
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
        vexDelay(5000);
        PID_turn(90, 0.1, 0.02);
        break;
    
    case 1:
        Hook.open();
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
    initialize_macros();
    while (true) {
        split_arcade();
        if (getControllerButtonX()) {
            Hook.close();
        }
        if (getControllerButtonY()) {
            Hook.close();
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
