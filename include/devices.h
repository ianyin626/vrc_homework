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
motor leftFront = motor(PORT20, ratio6_1, true);
motor leftMiddle = motor(PORT18, ratio6_1, true);
motor leftBack = motor(PORT10, ratio6_1, true);
motor rightFront = motor(PORT11, ratio6_1, false);
motor rightMiddle = motor(PORT1, ratio6_1, false);
motor rightBack = motor(PORT12, ratio6_1, false);
motor rightIntake = motor(PORT16, ratio6_1, false);
motor leftIntake = motor(PORT6, ratio6_1, true);
inertial Inertial = inertial(PORT3);

#define wheel_circumference_cm 25.93382
#define motor_to_wheel_gear_ratio 0.75
#define get_inertial Inertial.rotation(rotationUnits::deg)
#define get_gyroRate fabs(Inertial.gyroRate(zaxis, dps)) / 100
#define get_axis3 Controller.Axis3.position(percentUnits::pct)
#define get_axis1 Controller.Axis1.position(percentUnits::pct)
#define get_timer Brain.timer(timeUnits::msec)
#define get_position leftFront.position(rotationUnits::rev) * wheel_circumference_cm * motor_to_wheel_gear_ratio
#define get_motorRate leftFront.velocity(velocityUnits::dps) / 36000 * wheel_circumference_cm * motor_to_wheel_gear_ratio // TODO: Convert to mm/s, cm/s or in/s

#endif