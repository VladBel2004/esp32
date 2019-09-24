#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"

#ifndef _USR_MOTOR
#define _USR_MOTOR

// MOTOR Control Pins
#define MOTOR0_LEFT_PIN 17
#define MOTOR0_RIGHT_PIN 2

#define MOTOR1_LEFT_PIN 4
#define MOTOR1_RIGHT_PIN 16

// Motor Enums
typedef enum {
        MOTOR_ROT_LEFT = 1,
        MOTOR_ROT_RIGHT,
        MOTOR_ROT_STOP,
} motor_rot_t;

// Motor Structures
typedef struct {
        motor_rot_t motor0;
        motor_rot_t motor1;
} motor_cfg_t;

// Motor Funcs
motor_cfg_t motor_get_cfg_from_post( char *post_data );
esp_err_t motor_instruction_exec( char**messages, int len );

#endif
