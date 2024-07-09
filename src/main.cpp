/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Ian Yin                                                   */
/*    Created:      7/2/2024, 11:10:41 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "basic_functions.h"

using namespace vex;

competition Competition;

void pre_auton(void)
{

}

void autonomous(void)
{
    initialize();
    // PID_turn(90, 0.5, 0.015);
    PID_forward(200, 0.1, 0.01);
}

void usercontrol(void) {
    // if (Controller.ButtonL1.pressed()) {
    //     vex::task(intake_forward);
    // }
    // if (Controller.ButtonL2.pressed()) {
    //     vex::task(intake_backward);
    // }
    // if (Controller.ButtonR1.pressed()) {
    //     vex::task(intake_toggle_forward);
    // }
    // if (Controller.ButtonR1.pressed()) {
    //     vex::task(intake_toggle_forward);
    // }
    initialize_macros();
    split_arcade();
}

int main()
{
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    pre_auton();

    while (true)
    {
        wait(100, msec);
    }
}
