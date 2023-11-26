#include <stdio.h>
#include "string.h"
#include "esp_wifi.h"
#include "esp_now.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include <string.h>
#include <ds3231.h>
#include <time.h>
#include <sys/time.h>
#include "nvs_flash.h"
#include "esp_event.h"

#define ESP_CHANNEL 1
#define CONFIG_SDA_GPIO 21
#define CONFIG_SCL_GPIO 22

static const char *TAG = "esp_now_init";
static uint8_t peer_mac[ESP_NOW_ETH_ALEN] = {0xec, 0x62, 0x60, 0x84, 0x1f, 0x40}; // MAC rx vila

static esp_err_t init_wifi(void)
{
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();

    esp_netif_init();
    esp_event_loop_create_default();
    nvs_flash_init();
    esp_wifi_init(&wifi_init_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_storage(WIFI_STORAGE_FLASH);
    esp_wifi_start();

    ESP_LOGI(TAG, "WiFi init finished.");
    return ESP_OK;
}

void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    ESP_LOGI(TAG, "Message sent to MAC: " MACSTR ", Status: %s", MAC2STR(mac_addr), (status == ESP_NOW_SEND_SUCCESS) ? "Success" : "Fail");
}

static esp_err_t init_esp_now(void)
{
    esp_now_init();
    esp_now_register_send_cb(send_cb);

    ESP_LOGI(TAG, "ESP-NOW init finished.");
    return ESP_OK;
}

static esp_err_t register_peer(uint8_t *peer_mac)
{
    esp_now_peer_info_t esp_now_peer_info = {};
    memcpy(esp_now_peer_info.peer_addr, peer_mac, ESP_NOW_ETH_ALEN);
    esp_now_peer_info.channel = ESP_CHANNEL;
    esp_now_peer_info.ifidx = ESP_IF_WIFI_STA;
    esp_now_add_peer(&esp_now_peer_info);
    return ESP_OK;
}

void transmit_time_date(struct tm *timeinfo) {
    char message[50];
    sprintf(message, "Fecha y Hora: %04d-%02d-%02d %02d:%02d:%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    esp_now_send(peer_mac, (uint8_t *)message, sizeof(message));
}
// Función para obtener la hora del DS3231
void get_time_ds3231(void *pvParameters) {
    i2c_dev_t dev;
    memset(&dev, 0, sizeof(i2c_dev_t));
    ESP_ERROR_CHECK(ds3231_init_desc(&dev, 0, 21, 22));
    /*struct tm timeinfo = {
        .tm_year = 123, // (2022 - 1900)
        .tm_mon  = 10,  // 0-based
        .tm_mday = 6,
        .tm_hour = 11,
        .tm_min  = 12,
        .tm_sec  = 10
    };*/
    struct tm timeinfo;
    while (1) {
        if (ds3231_get_time(&dev, &timeinfo) == ESP_OK) {
            transmit_time_date(&timeinfo);
            ESP_LOGI(TAG, "Fecha y Hora: %04d-%02d-%02d %02d:%02d:%02d", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main() {
    ESP_ERROR_CHECK(init_wifi());
    ESP_ERROR_CHECK(init_esp_now());
    ESP_ERROR_CHECK(register_peer(peer_mac));
    ESP_ERROR_CHECK(i2cdev_init());

    xTaskCreate(get_time_ds3231, "get_time_ds3231", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);

}
