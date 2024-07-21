#include "devices.h"

// Define global variables
brain Brain;
controller Controller;
motor leftFront(PORT12, ratio6_1, true);
motor leftMiddle(PORT5, ratio6_1, true);
motor leftBack(PORT11, ratio6_1, false); // doens't work
motor rightFront(PORT4, ratio6_1, false); // doesn't work
motor rightMiddle(PORT2, ratio6_1, false);
motor rightBack(PORT16, ratio6_1, true); // doesn't work
motor leftIntake(PORT6, ratio6_1, false);
motor rightIntake(PORT17, ratio6_1, false);
motor puncher(PORT20, ratio6_1, false); // doesn't exist
optical opticalSensor(PORT3);
distance distanceSensor(PORT7);
inertial Inertial(PORT3); // doesn't exist
