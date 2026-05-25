#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "touch.h"
#include "fsm.h"
#include "oled.h"
#include "motor.h"
#include "microphone.h"
//prueba
void app_main(void)
{
    touch_init();

    oled_init();

    fsm_init();

    motor_init();

    //microphone_init();

    while(1)
    {
        fsm_update();

        motor_update();

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}