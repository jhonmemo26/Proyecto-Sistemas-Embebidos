#include "microphone.h"

#include <stdio.h>
#include <stdlib.h>

#include "driver/i2s_std.h"

#define I2S_WS     GPIO_NUM_32
#define I2S_SD     GPIO_NUM_35

static i2s_chan_handle_t rx_handle;


//====================================================
// Inicialización micrófono
//====================================================

void microphone_init(void)
{
    i2s_chan_config_t chan_cfg =
        I2S_CHANNEL_DEFAULT_CONFIG(
            I2S_NUM_0,
            I2S_ROLE_MASTER
        );

    i2s_new_channel(
        &chan_cfg,
        NULL,
        &rx_handle
    );

    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(16000),

        .slot_cfg = I2S_STD_MSB_SLOT_DEFAULT_CONFIG(
                        I2S_DATA_BIT_WIDTH_16BIT,
                        I2S_SLOT_MODE_MONO
                    ),

        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = I2S_WS,
            .ws = I2S_GPIO_UNUSED,
            .dout = I2S_GPIO_UNUSED,
            .din = I2S_SD,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };

    i2s_channel_init_std_mode(
        rx_handle,
        &std_cfg
    );

    i2s_channel_enable(rx_handle);

    printf("[MIC] Micrófono inicializado\n");
}


//====================================================
// Leer nivel sonido
//====================================================

int microphone_read_level(void)
{
    int16_t buffer[256];

    size_t bytes_read;

    i2s_channel_read(
        rx_handle,
        buffer,
        sizeof(buffer),
        &bytes_read,
        100
    );

    int samples = bytes_read / sizeof(int16_t);

    long sum = 0;

    for(int i = 0; i < samples; i++)
    {
        sum += abs(buffer[i]);
    }

    return sum / samples;
}