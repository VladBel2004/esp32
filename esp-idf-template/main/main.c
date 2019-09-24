#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "stdio.h"

#include "defs.h"

void app_main( void )
{
        esp_err_t ret = nvs_flash_init();
        if( ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND )
        {
                ESP_ERROR_CHECK( nvs_flash_erase() );
                ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK( ret );

        usr_gpio( NULL );

        ESP_ERROR_CHECK( esp_event_loop_create_default() );

        usr_wifi_start( NULL );
}
