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
extern motor roller;
extern motor lift;
extern distance distanceSensor;
extern optical opticalSensor;
extern inertial Inertial;
extern pneumatics mobileGoalHook;
extern pneumatics Arm;

#define DEBUG_MODE 1
#define PI 3.1415926535897932384626433832
#define WHEEL_DIAMETER_IN 3.25
#define WHEEL_CIRCUMFERENCE_CM WHEEL_DIAMETER_IN * 2.54 * PI
#define MOTOR_TO_WHEEL_GEAR_RATIO 0.75
#define INITIAL_HEADING 0
#define RING_COLOR_RED 1
#define RING_COLOR_BLUE 2
#define MIN_DRIVE_SPEED 10

inline double getInertial() {
    return Inertial.rotation(rotationUnits::deg);
}

inline double getGyroRate() {
    return Inertial.gyroRate(zaxis, dps) / 100; // degrees/10 ms
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
    return rightFront.position(rotationUnits::rev) * WHEEL_CIRCUMFERENCE_CM * MOTOR_TO_WHEEL_GEAR_RATIO;
}

inline double getMotorRate() {
    return leftFront.velocity(velocityUnits::dps) / 36000 * WHEEL_CIRCUMFERENCE_CM * MOTOR_TO_WHEEL_GEAR_RATIO; // cm/s
}

inline bool getControllerL1() {
    return Controller.ButtonL1.pressing();
}

inline bool getControllerL2() {
    return Controller.ButtonL2.pressing();
}

inline double getControllerButtonX() {
    return Controller.ButtonX.PRESSED;
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

inline double getControllerButtonDown() {
    return Controller.ButtonDown.PRESSED;
}

inline double getControllerButtonA() {
    return Controller.ButtonA.PRESSED;
}

inline double getControllerButtonB() {
    return Controller.ButtonB.PRESSED;
}

inline double getControllerButtonR1() {
    return Controller.ButtonR1.PRESSED;
}

inline double getControllerButtonR2() {
    return Controller.ButtonR2.PRESSED;
}

inline void grabMobileGoal() {
    mobileGoalHook.open();
}

inline void dropMobileGoal() {
    mobileGoalHook.close();
}

#endif
