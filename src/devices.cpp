#include "devices.h"

// Define global variables
brain Brain;
controller Controller;
motor leftFront(PORT20, ratio6_1, true);
motor leftMiddle(PORT18, ratio6_1, true);
motor leftBack(PORT10, ratio6_1, true);
motor rightFront(PORT11, ratio6_1, false);
motor rightMiddle(PORT1, ratio6_1, false);
motor rightBack(PORT12, ratio6_1, false);
motor rightIntake(PORT16, ratio6_1, false);
motor leftIntake(PORT6, ratio6_1, true);
motor puncher(PORT4, ratio6_1, true);
inertial Inertial(PORT3);
