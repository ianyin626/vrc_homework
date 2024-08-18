#include "devices.h"

// Define global variables
brain Brain;
controller Controller;
motor leftFront(PORT7, ratio6_1, true);
motor leftMiddle(PORT9, ratio6_1, true);
motor leftBack(PORT17, ratio6_1, true);
motor rightFront(PORT8, ratio6_1, true);
motor rightMiddle(PORT5, ratio6_1, true);
motor rightBack(PORT13, ratio6_1, true);
motor upIntake(PORT16, ratio6_1, false);
motor downIntake(PORT15, ratio6_1, false);
motor puncher(PORT19, ratio6_1, false); // doesn't exist
motor leftLift(PORT8, ratio18_1, true);
motor rightLift(PORT9, ratio18_1, false);
optical opticalSensor(PORT20);
optical opticalUp(PORT16);
distance distanceSensor(PORT13);
inertial Inertial(PORT14);
pneumatics Hook(Brain.ThreeWirePort.H);
pneumatics Arm(Brain.ThreeWirePort.D);