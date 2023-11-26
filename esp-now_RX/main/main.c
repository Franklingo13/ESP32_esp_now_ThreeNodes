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
#include "driver/gpio.h"
#include "ssd1306.h"

#define ESP_CHANNEL 1
#define LED_PIN GPIO_NUM_2

static uint8_t peer_mac[ESP_NOW_ETH_ALEN] = {0x40, 0x22, 0xd8, 0xef, 0x21, 0xd4}; // Mac Andres
static const char *TAG = "esp_now_init";

SSD1306_t dev;

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

void rec_cb(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len)
{
    char mac_str[18];
    sprintf(mac_str, MACSTR, MAC2STR(esp_now_info->src_addr));
    ESP_LOGI(TAG, "Message received from: %s, Message: %s", mac_str, data);

    // Actualizar la pantalla OLED con la dirección MAC y el mensaje recibido
    char display_text[64];
    sprintf(display_text, "MAC: %s", mac_str);
    ssd1306_clear_screen(&dev, false);
    ssd1306_contrast(&dev, 0xff);
    ssd1306_display_text(&dev, 0, display_text, 16, true);
    ssd1306_display_text(&dev, 2, "Message:", 16, false);
    ssd1306_display_text(&dev, 3, (char *)data, 16, false);
}

static esp_err_t init_esp_now(void)
{
    esp_now_init();
    esp_now_register_recv_cb(rec_cb);

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

void oled_task()
{
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    i2c_init(&dev, 128, 64);
    ssd1306_clear_screen(&dev, false);
    ssd1306_contrast(&dev, 0xff);
}

void app_main(void)
{
    ESP_ERROR_CHECK(init_wifi());
    ESP_ERROR_CHECK(init_esp_now());
    ESP_ERROR_CHECK(register_peer(peer_mac));

    oled_task(); // Inicializar la pantalla OLED

    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
