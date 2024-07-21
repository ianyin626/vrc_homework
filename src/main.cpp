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
int route = 0;


void pre_auton(void) {

}

void auton_route_1() {
    reverseTarget = 75;
    intake_positionCheck = true;
    task taskIntake(PID_forward_intake);
    PID_forward(150, 0.5, 0.05);
}

void auton_route_2() {
    PID_forward(100, 0.5, 0.05);
    PID_turn(180, 0.5, 0.015);
    PID_drift(270, 50, 50, 1, 0.1);
}

void auton_route_3() {
    target = 2100;   // ready: 1440 deg       launch: 2100
    puncher_move = true;
    task taskPuncher(puncher_control);
}

void autonomous(void) {
    continue_task = false;
    initialize();
    auton_route_1();
    double timer_start = Brain.timer(msec);
    switch (route) {
    case 0:
        // auton_route_1();
        break;

    case 1:
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
    double timer_end = Brain.timer(msec);
    logMessage("%.2f\n", timer_end - timer_start);
    while (1) {
        vexDelay(10);
    }
    
    // PID_turn(90, 0.5, 0.015);
    // PID_forward(100, 0.5, 0.05);
    // PID_drift(90, 50, 50, 1, 0.1);
}

void usercontrol(void) {
    continue_task = true;
    initialize_macros();
    puncher_move = true;
    target = 1440;
    task preset_puncher(puncher_control);
    logMessage("done presetting");
    task taskIntake(intake_control);

    while (1) {
        if (Controller.ButtonL1.pressing() && !Controller.ButtonL2.pressing() && !intakeStop) {
            logMessage("1");
            intake(100);
        } else if (Controller.ButtonL2.pressing() && !Controller.ButtonL1.pressing() && !intakeStop) {
            logMessage("2");
            intake(-100);
        } else if (!Controller.ButtonL1.pressing() && !Controller.ButtonL2.pressing()) {
            logMessage("3");
            intake(0);
        } else {
            logMessage("4");
            intake(0);
        }
        
        // split_arcade();
        if (Controller.ButtonY.PRESSED) {
            route = (route + 1) % 8;
            Controller.Screen.clearLine(4);
            Controller.Screen.setCursor(4, 1);
            switch (route) {
            case 0:
                Controller.Screen.print("route 1");
                break;
            
            case 1:
                Controller.Screen.print("route 2");
                break;
            
            case 2:
                Controller.Screen.print("route 3");
                break;

            case 3:
                Controller.Screen.print("route 4");
                break;
            
            case 4:
                Controller.Screen.print("route 5");
                break;

            case 5:
                Controller.Screen.print("route 6");
                break;

            case 6:
                Controller.Screen.print("route 7");
                break;

            case 7:
                Controller.Screen.print("route 8");
                break;
            }
        }
        vexDelay(10);
    }
}

int main() {
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    pre_auton();

    while (true)
    {
        wait(100, msec);
    }
}
