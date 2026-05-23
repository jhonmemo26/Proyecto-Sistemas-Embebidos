#include "touch.h"
#include "pins.h"

#include "driver/gpio.h"

void touch_init(void)
{
    gpio_reset_pin(TOUCH_PIN);
    gpio_set_direction(TOUCH_PIN, GPIO_MODE_INPUT);
}

bool touch_detected(void)
{
    return gpio_get_level(TOUCH_PIN);
}