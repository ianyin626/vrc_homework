#include "devices.h"
#include "basic_functions.h"
#include "utilities.h"


extern motor puncher;
int halfWayDone = 0;
int reverseTarget = 0;
bool intake_positionCheck = false;
bool puncher_move = false;
double target = 0;

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
            logMessage("%.2f", target - puncher.position(rotationUnits::deg));
        }
        vexDelay(10);
    }
    return 0;
}