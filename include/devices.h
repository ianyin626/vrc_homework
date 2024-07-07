#ifndef _devices_h
#define _devices_h

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
using namespace vex;

brain Brain = brain();
controller Controller = controller();
motor leftFront = motor(19, ratio6_1, true);
motor leftMiddle = motor(17, ratio6_1, true);
motor leftBack = motor(9, ratio6_1, true);
motor rightFront = motor(10, ratio6_1, false);
motor rightMiddle = motor(0, ratio6_1, false);
motor rightBack = motor(11, ratio6_1, false);
inertial Inertial = inertial(2);

#endif