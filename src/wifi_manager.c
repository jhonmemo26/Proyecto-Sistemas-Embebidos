#include "wifi_manager.h"

#include <stdio.h>
#include <string.h>

#include "config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "nvs_flash.h"

//==================================================
// WIFI INIT
//==================================================

void wifi_init()
{
    nvs_flash_init();

    esp_netif_init();

    esp_event_loop_create_default();

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg =
        WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {};

    strcpy(
        (char*)wifi_config.sta.ssid,
        WIFI_SSID
    );

    strcpy(
        (char*)wifi_config.sta.password,
        WIFI_PASSWORD
    );

    esp_wifi_set_mode(WIFI_MODE_STA);

    esp_wifi_set_config(
        WIFI_IF_STA,
        &wifi_config
    );

    esp_wifi_start();

    esp_wifi_connect();

    printf("CONNECTING WIFI...\n");

    wifi_ap_record_t ap_info;

    while(true)
    {
        esp_err_t err =
            esp_wifi_sta_get_ap_info(
                &ap_info
            );

        if(err == ESP_OK)
        {
            printf("WIFI CONNECTED\n");

            break;
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}