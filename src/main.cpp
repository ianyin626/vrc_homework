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
extern brain Brain;
extern inertial Inertial;
// A global instance of vex::brain used for printing to the V5 brain screen

// define your global instances of motors and other devices here


int main() {
    Brain.Screen.print("Starting...\n");
    printf("Calibrating...\n");
    Inertial.calibrate();
    while(Inertial.isCalibrating()) {
        vexDelay(10);
    }
    printf("Starting...\n");
    thread t_split_arcade = thread(split_arcade);
    // PID_turn(180, 1);

    // while (1) {
    //     Brain.Screen.clearScreen();
    //     Brain.Screen.print(Inertial.rotation(rotationUnits::deg));
    //     printf("Rotation: %f\n", Inertial.rotation(rotationUnits::deg));
    //     vexDelay(20);
    // }
    Brain.Screen.print("Ending...");
}
