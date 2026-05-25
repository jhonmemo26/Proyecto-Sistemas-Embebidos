#ifndef CONFIG_H
#define CONFIG_H

//==================================================
// WIFI
//==================================================

#define WIFI_SSID      "rpi4"
#define WIFI_PASSWORD  "Qwe12345"

//==================================================
// SERVER
//==================================================

#define SERVER_URL \
"http://172.20.10.2:8000/upload"

//==================================================
// AUDIO
//==================================================

#define SAMPLE_RATE      16000

#define RECORD_SECONDS   3

#define TOTAL_SAMPLES \
(SAMPLE_RATE * RECORD_SECONDS)

#define BUFFER_SIZE \
(TOTAL_SAMPLES * sizeof(int16_t))

//==================================================
// MIC PINS
//==================================================

#define MIC_CLK    GPIO_NUM_26

#define MIC_DATA   GPIO_NUM_32

#endif