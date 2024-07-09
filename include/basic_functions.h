#ifndef _basic_functions_h;
#define _basic_functions_h;

void move(double left_speed, double right_speed);
void split_arcade();
void PID_turn(double target, double error_tolerance, double speed_tolerance);
void PID_forward(double target, double error_tolerance, double speed_tolerance);
void intake_forward();
void intake_backward();
void intake_toggle_forward();
void intake_toggle_backward();
void intake_stop();
void initialize();
void initialize_macros();

#endif