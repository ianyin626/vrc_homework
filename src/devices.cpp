#include "devices.h"

// Define global variables
brain Brain;
controller Controller;
motor leftFront(PORT4, ratio6_1, true);
motor leftMiddle(PORT5, ratio6_1, true);
motor leftBack(PORT6, ratio6_1, true);
motor rightFront(PORT19, ratio6_1, false);
motor rightMiddle(PORT2, ratio6_1, false);
motor rightBack(PORT3, ratio6_1, false);
motor upIntake(PORT1, ratio6_1, true);
motor downIntake(PORT20, ratio6_1, false);
motor puncher(PORT19, ratio6_1, false); // doesn't exist
motor leftLift(PORT8, ratio18_1, true);
motor rightLift(PORT9, ratio18_1, false);
optical opticalSensor(PORT20);
optical opticalUp(PORT16);
distance distanceSensor(PORT13);
inertial Inertial(PORT14);
pneumatics Hook(Brain.ThreeWirePort.A);
pneumatics Arm(Brain.ThreeWirePort.D);