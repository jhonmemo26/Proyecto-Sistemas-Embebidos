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

    ssd1306_draw_bitmap(blink_bitmap);

    ssd1306_show();
}

void oled_wakeup_animation(void)
{
    ssd1306_clear();

    ssd1306_draw_bitmap(neutral_bitmap);

    ssd1306_show();
}

void oled_listening_animation(void)
{
    ssd1306_clear();

    ssd1306_draw_bitmap(happy_bitmap);

    ssd1306_show();
}

void oled_thinking_animation(void)
{
    ssd1306_clear();

    ssd1306_draw_bitmap(thinking_bitmap);

    ssd1306_show();
}

void oled_response_animation(void)
{
    ssd1306_clear();

    ssd1306_draw_bitmap(happy_bitmap);

    ssd1306_show();
}

void oled_show_awake(void)
{
    ssd1306_clear();

    ssd1306_draw_bitmap(neutral_bitmap);

    ssd1306_show();
}


void oled_show_blink(void)
{
    ssd1306_clear();

    ssd1306_draw_bitmap(neutral_bitmap);

    ssd1306_show();
}