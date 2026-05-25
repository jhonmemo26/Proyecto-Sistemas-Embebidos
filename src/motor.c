#include "motor.h"

#include "driver/gpio.h"

#define IN1 GPIO_NUM_33
#define IN2 GPIO_NUM_13
#define IN3 GPIO_NUM_27
#define IN4 GPIO_NUM_14

static int motor_delay_ms = 10;

#define STEPS_PER_REV 2048

static int step_index = 0;

static int current_steps = 0;

static int target_steps = 0;


//====================================================
// Secuencia Half-Step
//====================================================

static const int seq[8][4] = {

    {1,0,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,1},
    {0,0,0,1},
    {1,0,0,1}
};


//====================================================
// GPIO Step
//====================================================

static void write_step(int a,int b,int c,int d)
{
    gpio_set_level(IN1,a);
    gpio_set_level(IN2,b);
    gpio_set_level(IN3,c);
    gpio_set_level(IN4,d);
}


//====================================================
// Un paso
//====================================================

static void motor_step(int dir)
{
    step_index += dir;

    if(step_index > 7)
        step_index = 0;

    if(step_index < 0)
        step_index = 7;

    write_step(
        seq[step_index][0],
        seq[step_index][1],
        seq[step_index][2],
        seq[step_index][3]
    );
}


//====================================================
// Grados a pasos
//====================================================

static int deg_to_steps(int deg)
{
    return (deg * STEPS_PER_REV) / 360;
}


//====================================================
// Inicialización
//====================================================

void motor_init(void)
{
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask =
            (1ULL << IN1) |
            (1ULL << IN2) |
            (1ULL << IN3) |
            (1ULL << IN4)
    };

    gpio_config(&io_conf);

    write_step(0,0,0,0);
}


//====================================================
// Actualización continua motor
//====================================================

void motor_update(void)
{
    static int counter = 0;

    counter++;

    if(counter < motor_delay_ms)
        return;

    counter = 0;

    if(current_steps < target_steps)
    {
        motor_step(1);

        current_steps++;
    }
    else if(current_steps > target_steps)
    {
        motor_step(-1);

        current_steps--;
    }
}


//====================================================
// Movimiento cabeza
//====================================================

void head_move_left(int deg)
{
    target_steps -= deg_to_steps(deg);
}


void head_move_right(int deg)
{
    target_steps += deg_to_steps(deg);
}


void head_center(void)
{
    target_steps = 0;
}

void head_set_target(int deg)
{
    target_steps = deg_to_steps(deg);
}

void motor_set_speed(int delay_ms)
{
    motor_delay_ms = delay_ms;
}   