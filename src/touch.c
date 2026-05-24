#include "touch.h"
#include "pins.h"

#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static bool last_state = false;

static bool last_voice_state = false;


//====================================================
// Inicialización
//====================================================

void touch_init(void)
{
    // Touch principal
    gpio_reset_pin(TOUCH_PIN);

    gpio_set_direction(TOUCH_PIN,
                       GPIO_MODE_INPUT);


    // Touch voz
    gpio_reset_pin(VOICE_TOUCH_PIN);

    gpio_set_direction(VOICE_TOUCH_PIN,
                       GPIO_MODE_INPUT);


    // Esperar estabilización
    vTaskDelay(pdMS_TO_TICKS(200));


    // Leer estados iniciales
    last_state =
        gpio_get_level(TOUCH_PIN);

    last_voice_state =
        gpio_get_level(VOICE_TOUCH_PIN);
}


//====================================================
// Touch principal
//====================================================

bool touch_detected(void)
{
    bool current_state =
        gpio_get_level(TOUCH_PIN);

    // Detectar flanco subida
    if(current_state && !last_state)
    {
        vTaskDelay(pdMS_TO_TICKS(30));

        current_state =
            gpio_get_level(TOUCH_PIN);

        if(current_state)
        {
            last_state = true;

            return true;
        }
    }

    // Detectar liberación
    if(!current_state)
    {
        last_state = false;
    }

    return false;
}


//====================================================
// Touch voz
//====================================================

bool voice_touch_detected(void)
{
    bool current_state =
        gpio_get_level(VOICE_TOUCH_PIN);

    // Detectar flanco subida
    if(current_state && !last_voice_state)
    {
        vTaskDelay(pdMS_TO_TICKS(30));

        current_state =
            gpio_get_level(VOICE_TOUCH_PIN);

        if(current_state)
        {
            last_voice_state = true;

            return true;
        }
    }

    // Detectar liberación
    if(!current_state)
    {
        last_voice_state = false;
    }

    return false;
}