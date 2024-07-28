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
bool expectedRingColor = false; // true = blue, false = red

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
        if (opticalSensor.isNearObject() && (getOpticalHue() < 100) && expectedRingColor) {
            intakeReverse = true;
        } else if (opticalSensor.isNearObject() && (getOpticalHue() > 100) && !expectedRingColor) {
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