#ifndef _basic_functions_h;
#define _basic_functions_h;

void move(double left_speed, double right_speed);
void split_arcade();
void stop_all_motors();
void PID_turn(double target, double error_tolerance, double speed_tolerance);
void initialize();

#endif