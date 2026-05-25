#include "server_comm.h"

#include <stdio.h>
#include <string.h>

#include "config.h"

#include "audio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_http_client.h"

//==================================================
// URLS
//==================================================

#define GREETING_URL \
"http://172.20.10.2:8000/generate_greeting"

//==================================================
// SERVER RESPONSE
//==================================================

static char server_response[512];

//==================================================
// WAV HEADER
//==================================================

typedef struct {

    char riff[4];

    uint32_t overall_size;

    char wave[4];

    char fmt_chunk_marker[4];

    uint32_t length_of_fmt;

    uint16_t format_type;

    uint16_t channels;

    uint32_t sample_rate;

    uint32_t byterate;

    uint16_t block_align;

    uint16_t bits_per_sample;

    char data_chunk_header[4];

    uint32_t data_size;

} wav_header_t;

//==================================================
// SEND GREETING
//==================================================

void send_greeting()
{
    printf("\n");
    printf("========================\n");
    printf("GENERATING GREETING\n");
    printf("========================\n");

    esp_http_client_config_t config = {

        .url = GREETING_URL,

        .timeout_ms = 30000
    };

    esp_http_client_handle_t client =
        esp_http_client_init(
            &config
        );

    esp_http_client_set_method(
        client,
        HTTP_METHOD_GET
    );

    esp_err_t err =
        esp_http_client_perform(
            client
        );

    if(err == ESP_OK)
    {
        printf("GREETING READY\n");
    }
    else
    {
        printf("GREETING ERROR\n");
    }

    esp_http_client_cleanup(
        client
    );
}

//==================================================
// SEND AUDIO
//==================================================

void send_audio()
{
    int16_t* audio_buffer =
        get_audio_buffer();

    int audio_size =
        get_audio_size();

    wav_header_t wavHeader;

    memcpy(wavHeader.riff, "RIFF", 4);

    memcpy(wavHeader.wave, "WAVE", 4);

    memcpy(
        wavHeader.fmt_chunk_marker,
        "fmt ",
        4
    );

    memcpy(
        wavHeader.data_chunk_header,
        "data",
        4
    );

    wavHeader.length_of_fmt = 16;

    wavHeader.format_type = 1;

    wavHeader.channels = 1;

    wavHeader.sample_rate = SAMPLE_RATE;

    wavHeader.bits_per_sample = 16;

    wavHeader.byterate =
        SAMPLE_RATE *
        wavHeader.channels *
        wavHeader.bits_per_sample / 8;

    wavHeader.block_align =
        wavHeader.channels *
        wavHeader.bits_per_sample / 8;

    wavHeader.data_size =
        audio_size;

    wavHeader.overall_size =
        audio_size +
        sizeof(wav_header_t) - 8;

    esp_http_client_config_t config = {

        .url = SERVER_URL,

        .timeout_ms = 60000
    };

    esp_http_client_handle_t client =
        esp_http_client_init(
            &config
        );

    esp_http_client_set_method(
        client,
        HTTP_METHOD_POST
    );

    esp_http_client_set_header(
        client,
        "Content-Type",
        "audio/wav"
    );

    int total_size =
        sizeof(wav_header_t) +
        audio_size;

    esp_http_client_open(
        client,
        total_size
    );

    //==============================================
    // SEND WAV HEADER
    //==============================================

    esp_http_client_write(
        client,

        (const char*)&wavHeader,

        sizeof(wav_header_t)
    );

    //==============================================
    // SEND AUDIO CHUNKS
    //==============================================

    int offset = 0;

    while(offset < audio_size)
    {
        int chunk_size = 2048;

        if(offset + chunk_size > audio_size)
        {
            chunk_size =
                audio_size - offset;
        }

        int written =
            esp_http_client_write(
                client,

                ((char*)audio_buffer) + offset,

                chunk_size
            );

        if(written <= 0)
        {
            printf("WRITE ERROR\n");

            break;
        }

        offset += written;

        printf(
            "SENT %d / %d bytes\n",

            offset,

            audio_size
        );

        vTaskDelay(pdMS_TO_TICKS(10));
    }

    //==============================================
    // GET RESPONSE
    //==============================================

    esp_err_t err =
        esp_http_client_fetch_headers(
            client
        );

    if(err >= 0)
    {
        int len =
            esp_http_client_read_response(
                client,

                server_response,

                sizeof(server_response) - 1
            );

        if(len > 0)
        {
            server_response[len] = 0;

            printf("\nSERVER RESPONSE:\n");

            printf("%s\n", server_response);
        }
    }

    esp_http_client_close(client);

    esp_http_client_cleanup(client);
}

//==================================================
// GET RESPONSE
//==================================================

char* get_server_response()
{
    return server_response;
}