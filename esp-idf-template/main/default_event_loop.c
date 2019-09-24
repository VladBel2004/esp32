#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "tcpip_adapter.h"
#include "esp_event.h"
#include "esp_log.h"
#include "stdio.h"

#include "defs.h"

#define DEFINE_MAX_RETRY 5

static const char *TAG = "Default_Event_Loop";

int8_t try_retry = 0;

void default_event_loop_handler( void *event_arg, esp_event_base_t event_base, \
                int32_t event_id, void *event_data )
{
        if( event_base == WIFI_EVENT )
        {
                if( event_id == WIFI_EVENT_STA_START )
                {
                        esp_wifi_connect(); 
                }

                else if( event_id == WIFI_EVENT_STA_DISCONNECTED )
                {
                        usr_httpd_stop( NULL );

                        if( try_retry < DEFINE_MAX_RETRY )
                        {
                                esp_wifi_connect();
                                try_retry++;
                                ESP_LOGI( TAG, "Retry to connect to AP." );
                        }
                        ESP_LOGI( TAG, "Connected to AP fail." );
                }
        }

        else if( event_base == IP_EVENT )
        {
                if( event_id == IP_EVENT_STA_GOT_IP )
                {
                        uint8_t mac[6];
                        ESP_ERROR_CHECK( esp_wifi_get_mac( ESP_IF_WIFI_STA, mac ) );
                        ip_event_got_ip_t *sta_ip = (ip_event_got_ip_t*)event_data;

                        /*ESP_ERROR_CHECK( tcpip_adapter_set_hostname( TCPIP_ADAPTER_IF_STA, USR_STA_HOSTNAME ) );*/

                        printf( "STA got ip: %s;\n", ip4addr_ntoa( &sta_ip->ip_info.ip ) );
                        printf( "STA BSSID: %X:%X:%X:%X:%X:%X;\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5] );

                        try_retry = 0;

                        usr_httpd_start( NULL );
                }
        }
}
