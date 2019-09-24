#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_err.h"

#ifndef _USR_DEFFS
#define _USR_DEFFS

// Wi-Fi defines
#define USR_STA_HOSTNAME "localhost"

// Task Funcs.
void usr_wifi_start( void *arg );
void usr_httpd_start( void *arg );
void usr_httpd_stop( void *arg );

// USR String Funcs
char** usr_strsep( char *str, char sep, int *item_count );
void usr_freestrs( char **strs, int item_count );

// Event loop Funcs.
void default_event_loop_handler( void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,\
                void *event_data );

// gpio init func

esp_err_t usr_gpio( void *arg );

#endif
