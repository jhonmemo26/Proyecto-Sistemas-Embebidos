#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>

// Inicializa el OLED
void ssd1306_init(void);

// Limpia el framebuffer
void ssd1306_clear(void);

// Dibuja un bitmap completo 128x64
void ssd1306_draw_bitmap(const uint8_t *bitmap);

// Envía el framebuffer a la pantalla
void ssd1306_show(void);

#endif