#include "devices.h"

// Define global variables
brain Brain;
controller Controller;
motor leftFront(PORT1, ratio6_1, true);
motor leftMiddle(PORT2, ratio6_1, true);
motor leftBack(PORT3, ratio6_1, false);
motor rightFront(PORT4, ratio6_1, false);
motor rightMiddle(PORT5, ratio6_1, false);
motor rightBack(PORT6, ratio6_1, true);
motor leftIntake(PORT7, ratio6_1, false);
motor rightIntake(PORT20, ratio6_1, true);
motor puncher(PORT1, ratio6_1, false); // doesn't exist
optical opticalSensor(PORT20);
distance distanceSensor(PORT13);
inertial Inertial(PORT3); // doesn't exist
pneumatics Pneumatics(Brain.ThreeWirePort.A);