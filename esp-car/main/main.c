#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

int app_main(void)
{
        gpio_config_t config = {
                .pin_bit_mask = 1 << 2,
                .mode = GPIO_MODE_OUTPUT,
                .pull_up_en = 0,
                .pull_down_en = 0,
                .intr_type = 0,
        };

        gpio_config( &config );

        while( 1 )
        {
                gpio_set_level( 2, 1 );
                vTaskDelay( 500/portTICK_PERIOD_MS );
                gpio_set_level( 2, 0 );
                vTaskDelay( 500/portTICK_PERIOD_MS );
        }
}
