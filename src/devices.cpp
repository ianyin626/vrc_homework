#include "devices.h"

// Define global variables
brain Brain;
controller Controller;
motor leftFront(PORT17, ratio6_1, true);
motor leftMiddle(PORT19, ratio6_1, true);
motor leftBack(PORT5, ratio6_1, true);
motor rightFront(PORT11, ratio6_1, false);
motor rightMiddle(PORT18, ratio6_1, false);
motor rightBack(PORT12, ratio6_1, false);
motor upIntake(PORT10, ratio6_1, false);
motor downIntake(PORT2, ratio6_1, false);
motor lift(PORT7, ratio18_1, false);
optical opticalSensor(PORT21);
distance distanceSensor(PORT20); // N/A
inertial Inertial(PORT13);
pneumatics mobileGoalHook(Brain.ThreeWirePort.A);
pneumatics Arm(Brain.ThreeWirePort.D); // N/A