#include "devices.h"

// Define global variables
brain Brain;
controller Controller;
motor leftFront(PORT7, ratio6_1, true);
motor leftMiddle(PORT3, ratio6_1, true);
motor leftBack(PORT16, ratio6_1, false);
motor rightFront(PORT15, ratio6_1, false);
motor rightMiddle(PORT20, ratio6_1, false);
motor rightBack(PORT18, ratio6_1, true);
motor upIntake(PORT13, ratio6_1, true);
motor downIntake(PORT21, ratio6_1, false);
motor puncher(PORT19, ratio6_1, false); // doesn't exist
motor leftLift(PORT1, ratio18_1, true);
motor rightLift(PORT21, ratio18_1, false);
optical opticalSensor(PORT21);
optical opticalUp(PORT21);
distance distanceSensor(PORT21);
inertial Inertial(PORT14);
pneumatics Hook(Brain.ThreeWirePort.H);
pneumatics Arm(Brain.ThreeWirePort.D);