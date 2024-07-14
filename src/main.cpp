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

using namespace vex;

competition Competition;

int route = 0;


void pre_auton(void) {

}

void auton_route_1() {
    task taskCheck(position_check);
    task taskIntake(PID_forward_intake);
    task taskForward(PID_forward_100);
}

void autonomous(void) {
    initialize();
    double timer_start = Brain.timer(msec);
    switch (route) {
    case 0: 
        auton_route_1();
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
    printf("%f\n", timer_end - timer_start);
    while (1) {
        vexDelay(10);
    }
    
    // PID_turn(90, 0.5, 0.015);
    // PID_forward(100, 0.5, 0.05);
    // PID_drift(90, 50, 50, 1, 0.1);
}

void usercontrol(void) {
    initialize_macros();
    while (1) {
        split_arcade();
        if (Controller.ButtonY.PRESSED) {
            route = (route + 1) % 7;
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
