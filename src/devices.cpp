#include "devices.h"

// Define global variables
brain Brain;
controller Controller;
motor leftFront(PORT13, ratio6_1, true);
motor leftMiddle(PORT20, ratio6_1, true);
motor leftBack(PORT17, ratio6_1, false);
motor rightFront(PORT12, ratio6_1, false);
motor rightMiddle(PORT10, ratio6_1, false);
motor rightBack(PORT7, ratio6_1, true);
motor leftIntake(PORT16, ratio6_1, false);
motor rightIntake(PORT9, ratio6_1, true);
motor puncher(PORT1, ratio6_1, false); // doesn't exist
optical opticalSensor(PORT15);
distance distanceSensor(PORT11);
inertial Inertial(PORT3); // doesn't exist
pneumatics Pneumatics(Brain.ThreeWirePort.A);