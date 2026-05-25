//==================================================
// fsm.c
//==================================================

#include "fsm.h"

#include <stdio.h>
#include <stdbool.h>

#include "states.h"

#include "audio.h"
#include "server_comm.h"
#include "tts_player.h"
#include "motor.h"
#include "oled.h"
#include "touch.h"

//==================================================
// CURRENT STATE
//==================================================

static RobotState current_state =
    STATE_IDLE;

static int blink_counter = 0;

static bool blink_state = false;

static int wakeup_counter = 0;

//==================================================
// FSM INIT
//==================================================

void fsm_init()
{
    current_state = STATE_IDLE;

    printf("[FSM] INIT\n");
}

//==================================================
// FSM UPDATE
//==================================================

void fsm_update()
{
    switch(current_state)
    {
        //==========================================
        // IDLE
        //==========================================

        case STATE_IDLE:

            printf("[FSM] IDLE\n");

            motor_set_speed(12);

            head_center();

            blink_counter++;

            //======================================
            // BLINK
            //======================================

            if(!blink_state && blink_counter >= 80)
            {
                oled_show_blink();

                blink_state = true;

                blink_counter = 0;
            }
            else if(blink_state && blink_counter >= 8)
            {
                oled_idle_animation();

                blink_state = false;

                blink_counter = 0;
            }

            if(touch_detected())
            {
                printf("[FSM] TOUCH DETECTED\n");

                current_state =
                    STATE_DESPERTANDO;
            }

            break;

        //==========================================
        // DESPERTANDO
        //==========================================

        case STATE_DESPERTANDO:

            printf("[FSM] DESPERTANDO\n");

            motor_set_speed(8);

            wakeup_counter++;

            //======================================
            // PARPADEO
            //======================================

            if(wakeup_counter < 10)
            {
                oled_show_blink();
            }
            else
            {
                oled_wakeup_animation();
            }

            head_move_left(10);

            //======================================
            // ESPERAR UN POCO
            //======================================

            if(wakeup_counter >= 40)
            {
                wakeup_counter = 0;

                //==================================
                // GENERATE GREETING
                //==================================

                send_greeting();

                //==================================
                // PLAY GREETING
                //==================================

                play_tts();

                current_state =
                    STATE_ESCUCHANDO;
            }

            break;

        //==========================================
        // ESCUCHANDO
        //==========================================

        case STATE_ESCUCHANDO:

            printf("[FSM] ESCUCHANDO\n");

            motor_set_speed(4);

            oled_listening_animation();

            head_move_right(10);

            //======================================
            // RECORD AUDIO
            //======================================

            record_audio();

            current_state =
                STATE_PROCESANDO;

            break;

        //==========================================
        // PROCESANDO
        //==========================================

        case STATE_PROCESANDO:

            printf("[FSM] PROCESANDO\n");

            motor_set_speed(2);

            oled_thinking_animation();

            head_move_left(3);

            head_move_right(3);

            //======================================
            // SEND AUDIO
            //======================================

            send_audio();

            current_state =
                STATE_HABLANDO;

            break;

        //==========================================
        // HABLANDO
        //==========================================

        case STATE_HABLANDO:

            printf("[FSM] HABLANDO\n");

            motor_set_speed(5);

            oled_response_animation();

            head_move_left(5);

            //======================================
            // PLAY RESPONSE
            //======================================

            play_tts();

            head_move_right(5);

            current_state =
                STATE_IDLE;

            break;
    }
}