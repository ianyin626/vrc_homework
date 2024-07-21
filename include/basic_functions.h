#ifndef BASIC_FUNCTIONS_H;
#define BASIC_FUNCTIONS_H;
int continue_task;

void move(double left_speed, double right_speed);
void split_arcade();
void PID_turn(double target, double error_tolerance, double speed_tolerance);
void PID_forward(double target, double error_tolerance, double speed_tolerance);
void PID_drift(double target_angle, double base_speed, double max_speed, double error_tolerance, double speed_tolerance);
void intake(double volt);
void intake_backward();
void intake_toggle_forward();
void intake_toggle_backward();
void intake_stop();
void initialize();
void initialize_macros();

#endif