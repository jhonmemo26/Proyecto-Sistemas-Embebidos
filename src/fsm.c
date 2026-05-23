#include <stdio.h>

#include "fsm.h"
#include "states.h"
#include "touch.h"

static RobotState current_state;
static RobotState previous_state;

void fsm_init(void)
{
    current_state = STATE_IDLE;
    previous_state = -1;
}

void fsm_update(void)
{
    // Detectar entrada al estado
    if(current_state != previous_state)
    {
        previous_state = current_state;

        switch(current_state)
        {
            case STATE_IDLE:
                printf("[FSM] Estado: IDLE\n");
                break;

            case STATE_DESPERTANDO:
                printf("[FSM] Estado: DESPERTANDO\n");
                break;
        }
    }

    switch(current_state)
    {
        case STATE_IDLE:

            if(touch_detected())
            {
                printf("[FSM] Touch detectado\n");

                current_state = STATE_DESPERTANDO;
            }

            break;

        case STATE_DESPERTANDO:

            // Aqui luego iran:
            // motor
            // OLED
            // audio

            break;
    }
}