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
extern motor upIntake;
extern motor downIntake;
extern motor puncher;
extern motor leftLift;
extern motor rightLift;
extern distance distanceSensor;
extern optical opticalSensor;
extern optical opticalUp;
extern inertial Inertial;
extern pneumatics Hook;
extern pneumatics Arm;

#define DEBUG_MODE 1
#define PI 3.1415926535897932384626433832
#define WHEEL_DIAMETER_IN 3.25
#define WHEEL_CIRCUMFERENCE_CM WHEEL_DIAMETER_IN * 2.54 * PI
#define MOTOR_TO_WHEEL_GEAR_RATIO 0.75
#define INITIAL_HEADING 0

inline double getInertial() {
    return Inertial.rotation(rotationUnits::deg);
}

inline double getGyroRate() {
    return Inertial.gyroRate(zaxis, dps) / 100;
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
    return leftFront.velocity(velocityUnits::dps) / 36000 * WHEEL_CIRCUMFERENCE_CM * MOTOR_TO_WHEEL_GEAR_RATIO; // cm/10ms
}

inline double getControllerL1() {
    return Controller.ButtonL1.pressing();
}

inline double getControllerL2() {
    return Controller.ButtonL2.pressing();
}

inline double getControllerButtonX() {
    return Controller.ButtonY.PRESSED;
}

inline double getControllerButtonY() {
    return Controller.ButtonY.PRESSED;
}

inline double getOpticalHue() {
    return opticalSensor.hue();
}

inline double getIntakeForward() {
    
}

inline double getControllerButtonUp() {
    return Controller.ButtonUp.PRESSED;
}

#endif
