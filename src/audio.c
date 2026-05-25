#include "audio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/i2s_pdm.h"

//==================================================
// AUDIO BUFFER
//==================================================

static int16_t* audio_buffer = NULL;

//==================================================
// I2S HANDLE
//==================================================

static i2s_chan_handle_t rx_handle = NULL;

//==================================================
// AUDIO INIT
//==================================================

void audio_init()
{
    audio_buffer = malloc(BUFFER_SIZE);

    if(audio_buffer == NULL)
    {
        printf("AUDIO BUFFER FAILED\n");

        while(true)
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }

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

    i2s_pdm_rx_config_t pdm_rx_cfg = {

        .clk_cfg =
            I2S_PDM_RX_CLK_DEFAULT_CONFIG(
                SAMPLE_RATE
            ),

        .slot_cfg =
            I2S_PDM_RX_SLOT_DEFAULT_CONFIG(
                I2S_DATA_BIT_WIDTH_16BIT,
                I2S_SLOT_MODE_MONO
            ),

        .gpio_cfg = {

            .clk = MIC_CLK,

            .din = MIC_DATA,

            .invert_flags = {
                .clk_inv = false,
            }
        }
    };

    i2s_channel_init_pdm_rx_mode(
        rx_handle,
        &pdm_rx_cfg
    );

    i2s_channel_enable(
        rx_handle
    );

    printf("MIC READY\n");
}

//==================================================
// RECORD AUDIO
//==================================================

void record_audio()
{
    printf("\nRECORDING...\n");

    size_t bytes_read = 0;

    int samples_recorded = 0;

    while(samples_recorded < TOTAL_SAMPLES)
    {
        esp_err_t err =
            i2s_channel_read(
                rx_handle,

                &audio_buffer[samples_recorded],

                1024,

                &bytes_read,

                pdMS_TO_TICKS(1000)
            );

        if(err == ESP_OK)
        {
            int samples =
                bytes_read / sizeof(int16_t);

            samples_recorded += samples;

            printf(
                "%d / %d\n",

                samples_recorded,

                TOTAL_SAMPLES
            );
        }

        vTaskDelay(pdMS_TO_TICKS(1));
    }

    printf("RECORDING DONE\n");
}

//==================================================
// GETTERS
//==================================================

int16_t* get_audio_buffer()
{
    return audio_buffer;
}

int get_audio_size()
{
    return BUFFER_SIZE;
}