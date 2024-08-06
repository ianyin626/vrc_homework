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

int PID_forward_intake() {
    while (1) {
        if (intake_positionCheck) {
            int starting_position = getPosition();
            while ((getPosition() - starting_position) < reverseTarget) {
                intake(100);
                vexDelay(10);
            }
            intake(-100);
            intake_positionCheck = false;
        }
        vexDelay(10);
    }
    return 0;
}

int puncher_control() {
    puncher.setPosition(0, rotationUnits::deg);
    double kp = 1;
    while (1) {
        if (puncher_move) {
            puncher.spin(fwd, (target - puncher.position(rotationUnits::deg)) * kp * 120, voltageUnits::mV);
        }
        vexDelay(10);
    }
    return 0;
}

bool get_intake_detected() {
    if (distanceSensor.objectDistance(distanceUnits::mm) < 50) {
        return true;
    } else {
        return false;
    }
}

int intake_control() {
    while (1) {
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
    while(1) {
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
    while (1) {
        if (intakeReverse) {
            leftIntake.resetPosition();
                intake(0);
                vexDelay(10);
                logMessage("%.3f", leftIntake.position(rotationUnits::rev));
            intake(0);
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
    logMessage("unpushCabin: %d, %d, %d, %d, %d, %d", Cabin[2][0], Cabin[2][1], Cabin[1][0], Cabin[1][1], Cabin[0][0], Cabin[0][1]);
}

void clearCabin(int row) { // row is the first number in Cabin
    Cabin[row][0] = 0;
    Cabin[row][1] = 0;
    logMessage("clearCabin: %d", row);
}

// updateCabin is to make sure that the throwRing is accurate with where the ring actually is, as when the ring goes into the intake,
// it has to wait for the hook to hook up the intake.
void updateCabin(int row) {
    Cabin[row][0] = leftIntake.position(rotationUnits::deg) - 400; // ring leaving optical sensor pos - hook hooking up ring pos
}

int ringColor = 0; // 0 = NAN, 2 = blue, 1 = red
bool lastOpticalNearObject = false;
int detectRingStatus() {
    int lastRingColor = 0;
    while (1) {
        ringColor = 0;
        if ((opticalSensor.hue() < 40) && opticalSensor.isNearObject()) {
            ringColor = 1;
        } else if ((opticalSensor.hue() > 100) && opticalSensor.isNearObject()) {
            ringColor = 2;
        }
        if (lastRingColor != ringColor && ringColor != 0 && !intakeReversing) {
            pushCabin((int)leftIntake.position(rotationUnits::deg), ringColor);
        } else if (lastRingColor != ringColor && ringColor != 0 && intakeReversing) {
            unpushCabin();
        }
        if (lastRingColor != ringColor && ringColor == 0 && !intakeReversing) {
            updateCabin(0);
        }
        lastRingColor = ringColor;
        lastOpticalNearObject = opticalSensor.isNearObject();
        vexDelay(10);
    }
    return 0;
}

void throwRing() {
    double startingPosition = leftIntake.position(rotationUnits::deg);
    intake(-100);
    while (startingPosition - leftIntake.position(rotationUnits::deg) < 200) {
        vexDelay(10);
    }
    intake(0);
}

int detectRingLeave() {
    while (1) {
        for (int row = 2; row >= 0; row--) {
            if (Cabin[row][0] > 0 && ((leftIntake.position(rotationUnits::deg) - Cabin[row][0]) > 3600)) {
                clearCabin(row);
            }
            if (Cabin[row][0] > 0 && Cabin[row][1] != expectedRingColor && ((leftIntake.position(rotationUnits::deg) - Cabin[row][0]) > 2100)) {
                logMessage("Color,Row: %d %d", Cabin[row][1], row);
                throwRing();
            }
        }
        vexDelay(10);
    }
    return 0;
}