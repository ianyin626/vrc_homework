#include "devices.h"
#include "basic_functions.h"

int halfWayDone = 0;

int PID_forward_100() {
    PID_forward(100, 0.5, 0.05);

     return 0;
}

int position_check() {
    while (1) {
        if ((leftFront.position(vex::rotationUnits::rev) * WHEEL_CIRCUMFERENCE_CM * MOTOR_TO_WHEEL_GEAR_RATIO) > 50) {
            halfWayDone = 1;
        }
        vexDelay(10);
    }

    return 0;
}

int PID_forward_intake() {
    // leftFront.resetPosition();
    intake_forward();
    while (1) {
        if (halfWayDone == 1) {
            intake_backward();
        }
        vexDelay(10);
    }
    
    return 0;
}
