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
extern bool dropGoal;
extern double targetLiftPosition;
extern bool unjam;
extern bool jammed;

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
int forward_drop_goal();
int holdLift();
int unjamming();
#endif