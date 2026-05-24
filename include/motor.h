#ifndef MOTOR_H
#define MOTOR_H

void motor_init(void);

void motor_update(void);

void head_move_left(int deg);

void head_move_right(int deg);

void head_center(void);

void head_set_target(int deg);

void motor_set_speed(int delay_ms);

#endif