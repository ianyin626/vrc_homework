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

void autonomous(void) {
    initialize();
    PID_turn(90, 0.5, 0.015);
    // PID_forward(100, 0.5, 0.05);
    // PID_drift(90, 50, 50, 1, 0.1);
}

void usercontrol(void) {
    initialize_macros();
    while (1) {
        split_arcade();
        vexDelay(10);
    }
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
