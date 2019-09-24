#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_err.h"
#include "stdio.h"

#include "defs.h"
#include "motor.h"

esp_err_t usr_gpio( void *arg )
{
        gpio_config_t usr_gpio_cfg = {
                .pin_bit_mask = 1 << MOTOR0_LEFT_PIN  | 1 << MOTOR0_RIGHT_PIN | \
                                 1 << MOTOR1_LEFT_PIN  | 1 << MOTOR1_RIGHT_PIN,
                .mode = GPIO_MODE_OUTPUT,
                .pull_up_en = 0,
                .pull_down_en = 0,
                .intr_type = GPIO_INTR_DISABLE,
        };

        ESP_ERROR_CHECK( gpio_config( &usr_gpio_cfg ) );

        return ESP_OK;
}
