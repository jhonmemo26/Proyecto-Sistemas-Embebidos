//==================================================
// fsm.c
//==================================================

#include "fsm.h"

#include <stdio.h>

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

            oled_idle_animation();

            head_center();

            printf("[FSM] IDLE\n");

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

        //==================================================
        // fsm.c
        //==================================================

        case STATE_DESPERTANDO:

            printf("[FSM] DESPERTANDO\n");

            oled_wakeup_animation();

            head_move_left(10);

            //======================================
            // GENERATE GREETING
            //======================================

            send_greeting();

            //======================================
            // PLAY GREETING
            //======================================

            play_tts();

            current_state =
                STATE_ESCUCHANDO;

            break;

        //==========================================
        // ESCUCHANDO
        //==========================================

        case STATE_ESCUCHANDO:

            printf("[FSM] ESCUCHANDO\n");

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

            oled_thinking_animation();

            head_center();

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