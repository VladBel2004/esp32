#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "tcpip_adapter.h"
#include <esp_wifi.h>
#include <esp_wifi_types.h>
#include <stdio.h>

#define OUTPIN 18
#define OUTPUN_MASK ( 1ULL << OUTPIN ) 
#define delay 500

void wifi( void *arg )
{
        wifi_scan_config_t scan_config = {
                .ssid = NULL,
                .bssid = NULL,
                .channel = NULL,
                .show_hidden = 0,
        };
        uint16_t number_ap = 0;
        wifi_ap_record_t ap_recc[20];
        char *auth_mode;

        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        cfg.osi_funcs = NULL;
        ESP_ERROR_CHECK( esp_wifi_init( &cfg ) );
        ESP_ERROR_CHECK( esp_wifi_set_mode( WIFI_MODE_STA ) );
        ESP_ERROR_CHECK( esp_wifi_start() );
        ESP_ERROR_CHECK( esp_wifi_scan_start( &scan_config, 1 ) );
        esp_wifi_scan_get_ap_records( &number_ap, ap_recc );

        for( int i = 0; i < number_ap; i++ )
        {
                if( ap_recc[i].authmode == WIFI_AUTH_OPEN )
                        auth_mode = "OPEN";
                else
                        auth_mode = "LOCK";

                printf( "%i: SSID: %s; C: %i; PWR: %i; MODE: %s;", i, ap_recc[i].ssid, ap_recc[i].primary, ap_recc[i].rssi, auth_mode );
        }

        while( 1 )
        {

        }
}

void gpio( void * params )
{
        gpio_config_t gpio_cfg = 
        {
                .pin_bit_mask = OUTPUN_MASK,
                .mode = GPIO_MODE_OUTPUT,
                .pull_up_en = GPIO_PULLUP_DISABLE,
                .pull_down_en = GPIO_PULLDOWN_DISABLE,
                .intr_type = GPIO_INTR_DISABLE
        };

        gpio_config( &gpio_cfg );

        while( 1 )
        {
                gpio_set_level( OUTPIN, 1 );
                vTaskDelay( 1000 );
                gpio_set_level( OUTPIN, 0 );
                vTaskDelay( 1000 );
        }
}

