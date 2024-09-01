#include "devices.h"
#include "basic_functions.h"
#include "utilities.h"

int halfWayDone = 0;
int reverseTarget = 0;
bool intake_positionCheck = false;
bool puncher_move = false;
double target = 0;
bool continue_intake = false;
bool intakeStop = false;
bool last_ring_detected = false;
bool ring_detected = false;
bool intakeReverse = false;
int expectedRingColor = 0; // 0 = NAN, 1 = red, 2 = blue
bool intakeReversing = false;
int Cabin[3][2] = {{0, 0}, {0, 0}, {0, 0}};
bool dropGoal = false;

bool get_intake_detected() {
    if (distanceSensor.objectDistance(distanceUnits::mm) < 50) {
        return true;
    } else {
        return false;
    }
}

int intake_control() {
    while (true) {
        ring_detected = get_intake_detected();
        if (ring_detected && !last_ring_detected) {
            intakeStop = true;
        }
        if (!getControllerL1()) {
            intakeStop = false;
        }
        last_ring_detected = ring_detected;
        vexDelay(10);
    }
    return 0;
}

int opticalControl() {
    opticalSensor.setLight(ledState::on);
    while (true) {
        if (opticalSensor.isNearObject() && (getOpticalHue() < 100) && expectedRingColor == 2) {
            intakeReverse = true;
        } else if (opticalSensor.isNearObject() && (getOpticalHue() > 100) && expectedRingColor == 1) {
            intakeReverse = true;
        }
        vexDelay(10);
    }
    return 0;
}

int intakeReverseOptical() {
    while (true) {
        if (intakeReverse) {
            upIntake.resetPosition();
                // intake(0);
                vexDelay(10);
                logMessage("%.3f", upIntake.position(rotationUnits::rev));
            // intake(0);
            intakeReverse = false;
        }
        vexDelay(10);
    }
    return 0;
}

int getColor() {
    if (opticalSensor.hue() < 30 && opticalSensor.isNearObject()) {
        return 2; // red
    } else if (opticalSensor.hue() > 100) {
        return 1; // blue
    } else {
        return 0; // nothing
    }
}

void pushCabin(int Position, int Color) {
    Cabin[2][0] = Cabin[1][0];
    Cabin[2][1] = Cabin[1][1];
    Cabin[1][0] = Cabin[0][0];
    Cabin[1][1] = Cabin[0][1];
    Cabin[0][0] = Position;
    Cabin[0][1] = Color;
    logMessage("PushCabin: %d, %d, %d, %d, %d, %d", Cabin[2][0], Cabin[2][1], Cabin[1][0], Cabin[1][1], Cabin[0][0], Cabin[0][1]);
}

void unpushCabin() {
    Cabin[0][0] = Cabin[1][0];
    Cabin[0][1] = Cabin[1][1];
    Cabin[1][0] = Cabin[2][0];
    Cabin[1][1] = Cabin[2][1];
    Cabin[2][0] = 0;
    Cabin[2][1] = 0;
    logMessage("unpushCabin");
}

void clearCabin(int row) { // row is the first number in Cabin
    Cabin[row][0] = 0;
    Cabin[row][1] = 0;
    logMessage("clearCabin: %d", row);
}

int ringColor = 0; // 0 = NAN, 2 = blue, 1 = red
// int detectRingStatus() {
//     int lastRingColor = 0;
//     while (true) {
//         ringColor = 0;
//         if ((opticalSensor.hue() < 8) && opticalSensor.isNearObject()) {
//             ringColor = 1;
//             // logMessage("1");
//         } else if ((opticalSensor.hue() > 100) && opticalSensor.isNearObject()) {
//             ringColor = 2;
//             // logMessage("2");
//         }
//         if (lastRingColor != ringColor && ringColor != 0) {
//             pushCabin((int)upIntake.position(rotationUnits::deg), ringColor);
//         } else if (lastRingColor != ringColor && ringColor != 0) {
//             unpushCabin();
//         }
//         lastRingColor = ringColor;
//         lastOpticalNearObject = opticalSensor.isNearObject();
//         vexDelay(10);
//     }
//     return 0;
// }

void throwRing() {
    upIntake.setBrake(brakeType::brake);
    double startingPosition = upIntake.position(rotationUnits::deg);
    while (startingPosition - upIntake.position(rotationUnits::deg) > -100) {
        vexDelay(10);
    }
    intake(0);
    logMessage("throwDegree: %.0f", startingPosition - upIntake.position(rotationUnits::deg));
    vexDelay(1000);
    startingPosition = upIntake.position(rotationUnits::deg);
    intake(-100);
    while (startingPosition - upIntake.position(rotationUnits::deg) < 290) {
        vexDelay(10);
    }
    intake(0);
}

// int detectRingLeave() {
//     while (true) {
//         for (int row = 2; row >= 0; row--) {
//             if (Cabin[row][0] > 0 && ((upIntake.position(rotationUnits::deg) - Cabin[row][0]) > 3600)) {
//                 clearCabin(row);
//             }
//             if (Cabin[row][0] > 0 && Cabin[row][1] != expectedRingColor && ( (upIntake.position(rotationUnits::deg) - Cabin[row][0]) > 1250)) {
//                 logMessage("Color: %d, row: %d, Pos: %.0f", Cabin[row][1], row, upIntake.position(rotationUnits::deg) - Cabin[row][0]);
//                 throwRing();
//                 clearCabin(row);
//                 vexDelay(50);
//                 intake(100);
//             }
//         }
//         vexDelay(10);
//     }
//     return 0;
// }

int detectRingStatusUp() {
    int lastRingColor = 0;
    bool lastOpticalNearObject = false;
    while (true) {
        ringColor = 0;
        if ((opticalSensor.hue() < 30) && opticalSensor.isNearObject()) {
            ringColor = 1;
        } else if ((opticalSensor.hue() > 100) && opticalSensor.isNearObject()) {
            ringColor = 2;
        }
        if (lastRingColor != ringColor && ringColor != 0) {
            pushCabin((int)upIntake.position(rotationUnits::deg), ringColor);
        } else if (lastRingColor != ringColor && ringColor != 0) {
            unpushCabin();
        }
        lastRingColor = ringColor;
        lastOpticalNearObject = opticalSensor.isNearObject();
        vexDelay(10);
    }
    return 0;
}


int detectRingThrow() {
    bool lastOpticalNearObject = false;
    while (true) {
        for (int row = 2; row >= 0; row--) {
            if (Cabin[row][0] > 0 && ((upIntake.position(rotationUnits::deg) - Cabin[row][0]) > 3600)) {
                clearCabin(row);
            }
            if (Cabin[row][1] != 0 && Cabin[row][1] != expectedRingColor && !opticalSensor.isNearObject() && lastOpticalNearObject) {
                logMessage("Color: %d, row: %d, Pos: %.0f", Cabin[row][1], row, upIntake.position(rotationUnits::deg) - Cabin[row][0]);
                throwRing();
                clearCabin(row);
                vexDelay(50);
                intake(100);
            }
        }
        lastOpticalNearObject = opticalSensor.isNearObject();
        vexDelay(10);
    }
    return 0;
}

int detectRobotStatus() {
    while (true) {
        Brain.Screen.clearScreen();
        Controller.Screen.clearLine(4);
        Brain.Screen.printAt(0, 20, "leftFrontTemp: %.0f", leftFront.temperature(temperatureUnits::celsius));
        Brain.Screen.printAt(0, 40, "leftMiddleTemp: %.0f", leftMiddle.temperature(temperatureUnits::celsius));
        Brain.Screen.printAt(0, 60, "leftBackTemp: %.0f", leftBack.temperature(temperatureUnits::celsius));
        Brain.Screen.printAt(200, 20, "rightFront: %.0f", rightFront.temperature(temperatureUnits::celsius));
        Brain.Screen.printAt(200, 40, "rightMiddle: %.0f", rightMiddle.temperature(temperatureUnits::celsius));
        Brain.Screen.printAt(200, 60, "rightBack: %.0f", rightBack.temperature(temperatureUnits::celsius));

        Brain.Screen.printAt(0, 100, "IntakeTemp: %.0f", upIntake.temperature(temperatureUnits::celsius));
        Brain.Screen.printAt(200, 100, "IntakeVoltage: %.0f", upIntake.voltage(voltageUnits::mV));
        Brain.Screen.printAt(0, 120, "IntakeRPM: %.0f", upIntake.velocity(velocityUnits::rpm));

        Brain.Screen.printAt(0, 140, "leftLiftTemp: %.0f", leftLift.temperature(temperatureUnits::celsius));
        Brain.Screen.printAt(200, 140, "rightLiftTemp: %.0f", rightLift.temperature(temperatureUnits::celsius));

        Controller.Screen.setCursor(4, 1);
        Controller.Screen.print("rotation: %5.0f_______", Inertial.rotation(rotationUnits::deg));
        vexDelay(500);
    }
    return 0;
}

int autonRouteSelect() {
    Controller.Screen.print("Route: %d", route + 1);
    while (true) {
        if(getControllerButtonY()) {
            route++;
            route = route % 8;
            Controller.Screen.clearLine(4);
            Controller.Screen.setCursor(4, 1);
            Controller.Screen.print("Route: %d", route + 1);
            logMessage("switch route");
        }
        vexDelay(10);
    }
    return 0;
}

int intakeUnjamming() {
    while (true) {
        if (upIntake.current(currentUnits::amp) > 0.7 && fabs(upIntake.velocity(velocityUnits::pct)) < 2) {
            intake(-100);
            vexDelay(300);
            intake(100);
        }
        vexDelay(10);
    }
    return 0;
}