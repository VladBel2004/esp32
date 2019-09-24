#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "stdio.h"


void app_main( void )
{
        gpio_config_t cfg = {
                .pin_bit_mask = 1 << 15 | 1 << 2,
                .mode = GPIO_MODE_OUTPUT,
                .pull_up_en = 0,
                .pull_down_en = 0,
                .intr_type = GPIO_INTR_DISABLE,
        };

        ESP_ERROR_CHECK( gpio_config( &cfg ) );

        while( true )
        {
                gpio_set_level( 15, 1 );
        }
        return false;
}
