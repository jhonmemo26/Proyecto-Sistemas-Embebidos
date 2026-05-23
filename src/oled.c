#include "oled.h"

#include "ssd1306.h"
#include "bitmaps.h"

void oled_init(void)
{
    ssd1306_init();
}

void oled_idle_animation(void)
{
    ssd1306_clear();

    ssd1306_draw_bitmap(sleepy_eyes_bitmap);

    ssd1306_show();
}

void oled_wakeup_animation(void)
{
    ssd1306_clear();

    ssd1306_draw_bitmap(awake_eyes_bitmap);

    ssd1306_show();
}

void oled_listening_animation(void)
{

}

void oled_thinking_animation(void)
{

}

void oled_response_animation(void)
{

}