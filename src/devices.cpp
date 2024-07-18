#include "devices.h"

// Define global variables
brain Brain;
controller Controller;
motor leftFront(PORT11, ratio6_1, true);
motor leftMiddle(PORT6, ratio6_1, true);
motor leftBack(PORT12, ratio6_1, false);
motor rightFront(PORT1, ratio6_1, false);
motor rightMiddle(PORT2, ratio6_1, false);
motor rightBack(PORT16, ratio6_1, true);
motor forwardIntake(PORT4, ratio6_1, false);
motor backwardIntake(PORT17, ratio6_1, true);
motor puncher(PORT20, ratio6_1, false); // doesn't exist
inertial Inertial(PORT3); // doesn't exist
