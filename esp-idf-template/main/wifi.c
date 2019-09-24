#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tcpip_adapter.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"

#include "defs.h"

#define USR_SSID "ELEKTRONIKA"
#define USR_PWD "78051117"

static const char *TAG = "Wi-Fi";

void usr_wifi_start( void *arg )
{
        wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();

        wifi_config_t wifi_config = {
                .sta = {
                        .ssid = USR_SSID,
                        .password = USR_PWD,
                },
        };

        ESP_ERROR_CHECK( esp_event_handler_register( WIFI_EVENT, ESP_EVENT_ANY_ID, &default_event_loop_handler, NULL ) );
        ESP_ERROR_CHECK( esp_event_handler_register( IP_EVENT, ESP_EVENT_ANY_ID, &default_event_loop_handler, NULL ) );

        tcpip_adapter_init();

        ESP_ERROR_CHECK( esp_wifi_init( &wifi_init_config ) );
        ESP_ERROR_CHECK( esp_wifi_set_mode( WIFI_MODE_STA ) );
        ESP_ERROR_CHECK( esp_wifi_set_config( ESP_IF_WIFI_STA, &wifi_config ) );
        ESP_ERROR_CHECK( esp_wifi_start() );

        ESP_LOGI( TAG, "Wi-Fi inti finish." );

}
