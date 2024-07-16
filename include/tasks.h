#ifndef TASKS_H
#define TASKS_H
extern bool intake_positionCheck;
extern int reverseTarget;
extern bool puncher_move;
extern double target;

int PID_forward_intake();
int puncher_control();

#endif