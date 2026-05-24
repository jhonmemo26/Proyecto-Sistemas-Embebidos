#include <stdio.h>
#include <stdbool.h>

#include "fsm.h"
#include "states.h"

#include "touch.h"
#include "oled.h"
#include "motor.h"

static RobotState current_state;
static RobotState previous_state;

static int head_direction = 1;

static int counter = 0;

static int blink_counter = 0;

static bool blink_state = false;

static int wakeup_counter = 0;

static int listening_timeout = 0;


//====================================================
// Inicialización FSM
//====================================================

void fsm_init(void)
{
    current_state = STATE_IDLE;

    previous_state = -1;
}


//====================================================
// Actualización FSM
//====================================================

void fsm_update(void)
{
    //================================================
    // Detectar cambio de estado
    //================================================

    if(current_state != previous_state)
    {
        previous_state = current_state;

        switch(current_state)
        {
            //========================================
            // ESTADO IDLE
            //========================================

            case STATE_IDLE:

                printf("[FSM] Estado: IDLE\n");

                oled_idle_animation();

                head_center();


                break;


            //========================================
            // ESTADO DESPERTANDO
            //========================================

            case STATE_DESPERTANDO:

                printf("[FSM] Estado: DESPERTANDO\n");

                oled_wakeup_animation();

                   motor_set_speed(2);

                break;


            //========================================
            // ESTADO ESCUCHANDO
            //========================================

            case STATE_ESCUCHANDO:

                printf("[FSM] Estado: ESCUCHANDO\n");

                oled_listening_animation();

                head_center();

                break;


            //========================================
            // ESTADO PROCESANDO
            //========================================

            case STATE_PROCESANDO:

                printf("[FSM] Estado: PROCESANDO\n");

                oled_thinking_animation();

                motor_set_speed(1);

                break;
        }
    }


    //================================================
    // Lógica continua de estados
    //================================================

    switch(current_state)
    {
        //============================================
        // IDLE
        //============================================

        case STATE_IDLE:

            if(touch_detected())
            {
                printf("[FSM] Touch detectado\n");

                current_state = STATE_DESPERTANDO;
            }

            break;


        //============================================
        // DESPERTANDO
        //============================================

        case STATE_DESPERTANDO:

            //========================================
            // Movimiento cabeza
            //========================================

            counter++;

            if(counter >= 140)
            {
                counter = 0;

                if(head_direction)
                {
                    head_set_target(60);
                }
                else
                {
                    head_set_target(-60);
                }

                head_direction = !head_direction;
            }


            //========================================
            // Parpadeo OLED
            //========================================

            blink_counter++;

            if(!blink_state && blink_counter >= 200)
            {
                oled_show_blink();

                blink_state = true;

                blink_counter = 0;
            }

            if(blink_state && blink_counter >= 15)
            {
                oled_show_awake();

                blink_state = false;

                blink_counter = 0;
            }


            //========================================
            // Cambio a ESCUCHANDO
            //========================================

            wakeup_counter++;

            if(wakeup_counter >= 500)
            {
                wakeup_counter = 0;

                current_state = STATE_ESCUCHANDO;
            }

            break;


        //============================================
        // ESCUCHANDO
        //============================================

        case STATE_ESCUCHANDO:

            listening_timeout++;

            //========================================
            // Timeout -> volver a IDLE
            //========================================

            if(listening_timeout >= 800)
            {
                listening_timeout = 0;

                current_state = STATE_IDLE;
            }


            //========================================
            // TEMPORAL:
            // simulación detección voz
            //========================================

           if(voice_touch_detected())
{
    listening_timeout = 0;

    current_state = STATE_PROCESANDO;
}

            break;


        //============================================
        // PROCESANDO
        //============================================

        case STATE_PROCESANDO:

    counter++;

    if(counter >= 180)
    {
        counter = 0;

        if(head_direction)
        {
            head_set_target(20);
        }
        else
        {
            head_set_target(-20);
        }

        head_direction = !head_direction;
    }

    break;
    }
}
