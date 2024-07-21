#ifndef DEVICES_H
#define DEVICES_H

#include "vex.h"

using namespace vex;

// Declare global variables
extern brain Brain;
extern controller Controller;
extern motor leftFront;
extern motor leftMiddle;
extern motor leftBack;
extern motor rightFront;
extern motor rightMiddle;
extern motor rightBack;
extern motor leftIntake;
extern motor rightIntake;
extern motor puncher;
extern distance distanceSensor;
extern inertial Inertial;

#define DEBUG_MODE 1
#define WHEEL_CIRCUMFERENCE_CM 31.9185
#define MOTOR_TO_WHEEL_GEAR_RATIO 0.75
#define INITIAL_HEADING 0

inline double getInertial() {
    return Inertial.rotation(rotationUnits::deg);
}

inline double getGyroRate() {
    return fabs(Inertial.gyroRate(zaxis, dps)) / 100;
}

inline int getAxis3() {
    return Controller.Axis3.position(percentUnits::pct);
}

inline int getAxis1() {
    return Controller.Axis1.position(percentUnits::pct);
}

inline double getTimer() {
    return Brain.timer(timeUnits::msec);
}

inline double getPosition() {
    return leftFront.position(rotationUnits::rev) * WHEEL_CIRCUMFERENCE_CM * MOTOR_TO_WHEEL_GEAR_RATIO;
}

inline double getMotorRate() {
    return leftFront.velocity(velocityUnits::dps) / 36000 * WHEEL_CIRCUMFERENCE_CM * MOTOR_TO_WHEEL_GEAR_RATIO; // cm/s
}

#endif
