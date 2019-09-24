#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "string.h"
#include "stdio.h"

#include "defs.h"
#include "motor.h"

esp_err_t motor_instruction_exec( char**messages, int len )
{
        for( int i = 0; i < len; i++ )
        {
                if( strcmp( messages[i], "motor0=right" ) == 0 )
                {
                        gpio_set_level( MOTOR0_LEFT_PIN, 0 );
                        gpio_set_level( MOTOR0_RIGHT_PIN, 1 );
                }
                else if( strcmp( messages[i], "motor0=left" ) == 0 )
                {  
                        gpio_set_level( MOTOR0_LEFT_PIN, 1 );
                        gpio_set_level( MOTOR0_RIGHT_PIN, 0 );
                }
                else if( strcmp( messages[i], "motor0=stop" ) == 0 )
                {
                        gpio_set_level( MOTOR0_LEFT_PIN, 0 );
                        gpio_set_level( MOTOR0_RIGHT_PIN, 0 );
                }
                else if( strcmp( messages[i], "motor1=left" ) == 0 )
                {
                        gpio_set_level( MOTOR1_LEFT_PIN, 1 );
                        gpio_set_level( MOTOR1_RIGHT_PIN, 0 );
                }
                else if( strcmp( messages[i], "motor1=right" ) == 0 )
                {
                        gpio_set_level( MOTOR1_LEFT_PIN, 0 );
                        gpio_set_level( MOTOR1_RIGHT_PIN, 1 );
                }
                else if( !strcmp( messages[i], "motor1=stop" ) == 0 )
                {
                        gpio_set_level( MOTOR1_LEFT_PIN, 0 );
                        gpio_set_level( MOTOR1_RIGHT_PIN, 0 );
                }
        }
        
        return ESP_OK;
}
