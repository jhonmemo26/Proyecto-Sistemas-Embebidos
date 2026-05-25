#include "tts_player.h"

#include <stdio.h>
#include <stdint.h>

#include "driver/dac.h"

#include "esp_http_client.h"

#include "esp_rom_sys.h"

//==================================================
// SERVER URL
//==================================================

#define TTS_URL \
"http://172.20.10.2:8000/tts"

//==================================================
// PLAY TTS
//==================================================
void play_greeting()
{
    printf("HOLA SOY CRAIBOT\n");

    // luego aquí puedes poner
    // un audio PCM local

    vTaskDelay(
        pdMS_TO_TICKS(2000)
    );
}
void play_tts()
{
    printf("\n");
    printf("========================\n");
    printf("PLAYING TTS\n");
    printf("========================\n");

    //==============================================
    // ENABLE DAC GPIO25
    //==============================================

    dac_output_enable(DAC_CHANNEL_1);

    printf("DAC ENABLED GPIO25\n");

    //==============================================
    // HTTP CONFIG
    //==============================================

    esp_http_client_config_t config = {

        .url = TTS_URL,

        .timeout_ms = 60000
    };

    esp_http_client_handle_t client =
        esp_http_client_init(
            &config
        );

    esp_http_client_set_method(
        client,
        HTTP_METHOD_GET
    );

    //==============================================
    // OPEN CONNECTION
    //==============================================

    if(
        esp_http_client_open(client, 0)
        != ESP_OK
    )
    {
        printf("TTS CONNECTION FAILED\n");

        return;
    }

    printf("CONNECTED TO TTS SERVER\n");
    int content_length =
        esp_http_client_fetch_headers(
            client
        );

    printf(
        "CONTENT LENGTH: %d\n",
        content_length
    );
    //==============================================
    // STREAM BUFFER
    //==============================================

    uint8_t buffer[1024];

    int total_samples = 0;

    int total_bytes = 0;

    //==============================================
    // STREAM PCM
    //==============================================

    while(true)
    {
        int bytes_read =
            esp_http_client_read(
                client,

                (char*)buffer,

                sizeof(buffer)
            );

        //==========================================
        // ERROR
        //==========================================

        if(bytes_read < 0)
        {
            printf("HTTP READ ERROR\n");

            break;
        }

        //==========================================
        // END OF AUDIO
        //==========================================

        if(bytes_read == 0)
        {
            printf("NO MORE AUDIO DATA\n");

            break;
        }

        total_bytes += bytes_read;

        printf(
            "RECEIVED %d BYTES | TOTAL %d\n",
            bytes_read,
            total_bytes
        );

        //==========================================
        // PLAY PCM
        //==========================================

        for(int i = 0; i < bytes_read - 1; i += 2)
        {
            //======================================
            // 16-BIT PCM SAMPLE
            //======================================

            int16_t sample =
                buffer[i] |
                (buffer[i + 1] << 8);

            //======================================
            // DEBUG FIRST SAMPLES
            //======================================

            if(total_samples < 20)
            {
                printf(
                    "SAMPLE %d = %d\n",
                    total_samples,
                    sample
                );
            }

            //======================================
            // VOLUME
            //======================================

            sample /= 1;

            //======================================
            // PCM -> DAC
            //======================================

            uint8_t dac_value =
                (sample + 32768) >> 8;

            //======================================
            // OUTPUT AUDIO
            //======================================

            dac_output_voltage(
                DAC_CHANNEL_1,

                dac_value
            );

            //======================================
            // 24kHz SAMPLE RATE
            //======================================

            esp_rom_delay_us(42);

            total_samples++;
        }
    }

    //==============================================
    // SILENCE
    //==============================================

    dac_output_voltage(
        DAC_CHANNEL_1,
        128
    );

    printf("\n");
    printf("========================\n");
    printf("TTS PLAYBACK FINISHED\n");
    printf("========================\n");

    printf(
        "TOTAL BYTES RECEIVED: %d\n",
        total_bytes
    );

    printf(
        "TOTAL SAMPLES PLAYED: %d\n",
        total_samples
    );

    //==============================================
    // CHECK IF AUDIO WAS RECEIVED
    //==============================================

    if(total_samples == 0)
    {
        printf("\n");
        printf("ERROR: NO AUDIO SAMPLES PLAYED\n");
    }
    else
    {
        printf("\n");
        printf("AUDIO PLAYED SUCCESSFULLY\n");
    }

    //==============================================
    // CLEANUP
    //==============================================

    esp_http_client_close(client);

    esp_http_client_cleanup(client);

    printf("\n");
    printf("========================\n");
    printf("TTS DONE\n");
    printf("========================\n");
}