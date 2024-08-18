#ifndef TASKS_H
#define TASKS_H
extern bool intake_positionCheck;
extern int reverseTarget;
extern bool last_ring_detected;
extern bool puncher_move;
extern bool continue_intake;
extern bool get_intake_detected();
extern bool intakeStop;
extern int expectedRingColor;
extern bool intakeReverse;
extern double target;
extern bool intakeReversing;

int PID_forward_intake();
int puncher_control();
int intake_control();
int opticalControl();
int intakeReverseOptical();
int getColor();
int detectRingStatus();
int detectRingLeave();
int detectRobotStatus();
int autonRouteSelect();
int detectRingThrow();
int detectRingStatusUp();

#endif