#include "ssd1306.h"

#include <string.h>

#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define I2C_PORT        I2C_NUM_0

#define SDA_PIN         21
#define SCL_PIN         22

#define OLED_ADDR       0x3C

#define OLED_WIDTH      128
#define OLED_HEIGHT     64

static i2c_master_bus_handle_t bus_handle;
static i2c_master_dev_handle_t oled_handle;

// Framebuffer completo
static uint8_t framebuffer[OLED_WIDTH * OLED_HEIGHT / 8];


//====================================================
// Enviar comando al SSD1306
//====================================================

static void ssd1306_send_command(uint8_t cmd)
{
    uint8_t data[2];

    data[0] = 0x00;
    data[1] = cmd;

    i2c_master_transmit(oled_handle, data, 2, -1);
}


//====================================================
// Inicialización I2C + SSD1306
//====================================================

void ssd1306_init(void)
{
    // Configuración del bus I2C
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_PORT,
        .sda_io_num = SDA_PIN,
        .scl_io_num = SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true
    };

    i2c_new_master_bus(&bus_config, &bus_handle);

    // Configuración del dispositivo OLED
    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = OLED_ADDR,
        .scl_speed_hz = 400000
    };

    i2c_master_bus_add_device(bus_handle, &dev_config, &oled_handle);

    vTaskDelay(pdMS_TO_TICKS(100));

    // Secuencia de inicialización SSD1306
    ssd1306_send_command(0xAE);

    ssd1306_send_command(0x20);
    ssd1306_send_command(0x00);

    ssd1306_send_command(0xB0);

    ssd1306_send_command(0xC8);

    ssd1306_send_command(0x00);
    ssd1306_send_command(0x10);

    ssd1306_send_command(0x40);

    ssd1306_send_command(0x81);
    ssd1306_send_command(0xFF);

    ssd1306_send_command(0xA1);

    ssd1306_send_command(0xA6);

    ssd1306_send_command(0xA8);
    ssd1306_send_command(0x3F);

    ssd1306_send_command(0xD3);
    ssd1306_send_command(0x00);

    ssd1306_send_command(0xD5);
    ssd1306_send_command(0xF0);

    ssd1306_send_command(0xD9);
    ssd1306_send_command(0x22);

    ssd1306_send_command(0xDA);
    ssd1306_send_command(0x12);

    ssd1306_send_command(0xDB);
    ssd1306_send_command(0x20);

    ssd1306_send_command(0x8D);
    ssd1306_send_command(0x14);

    ssd1306_send_command(0xAF);

    ssd1306_clear();

    ssd1306_show();
}


//====================================================
// Limpiar framebuffer
//====================================================

void ssd1306_clear(void)
{
    memset(framebuffer, 0x00, sizeof(framebuffer));
}


//====================================================
// Dibujar bitmap completo
//====================================================

void ssd1306_draw_bitmap(const uint8_t *bitmap)
{
    memcpy(framebuffer, bitmap, sizeof(framebuffer));
}


//====================================================
// Enviar framebuffer al OLED
//====================================================

void ssd1306_show(void)
{
    for(int page = 0; page < 8; page++)
    {
        ssd1306_send_command(0xB0 + page);

        ssd1306_send_command(0x00);

        ssd1306_send_command(0x10);

        uint8_t data[129];

        data[0] = 0x40;

        memcpy(&data[1],
               &framebuffer[OLED_WIDTH * page],
               OLED_WIDTH);

        i2c_master_transmit(oled_handle,
                            data,
                            sizeof(data),
                            -1);
    }
}
