#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_http_server.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "defs.h"
#include "httpd.h"
#include "html_pages.h"
#include "motor.h"

static const char *TAG = "HTTPD";

int usr_gpio_pin_pos = 0;

esp_err_t usr_httpd_root_get_handler( httpd_req_t *httpd_req )
{
        char *buffer;
        /*size_t len;*/

        printf( "uri /root called.\n" );

        /*len = httpd_req_get_hdr_value_len( httpd_req, "Host" ) + 1;*/
        /*if( len > 1 )*/
        /*{*/
                /*buffer = malloc( len );*/
                /*if( httpd_req_get_hdr_value_str( httpd_req, "Host", buffer, len ) == ESP_OK )*/
                /*{*/
                        /*if( strcmp( buffer, "localhost" ) != 0 )*/
                        /*{*/
                                /*httpd_resp_send_err( httpd_req, HTTPD_400_BAD_REQUEST, "NULL" );*/
                                /*return ESP_FAIL;*/
                        /*}*/
                /*}*/
                
                /*free( buffer );*/
        /*}*/

        buffer = malloc( strlen( root_page ) + 1 );

        httpd_resp_set_status( httpd_req, "200 OK" );
        httpd_resp_set_type( httpd_req, "text/html" );
        httpd_resp_set_hdr( httpd_req, "Server", "esp_http_server" );

        free( buffer );

        httpd_resp_send( httpd_req, root_page, strlen(root_page) );
        printf( "return\n" );

        return ESP_OK;
}

esp_err_t usr_httpd_root_post_handler( httpd_req_t *httpd_req )
{
        char *buffer = NULL;
        size_t len = 0;
        int mlen = 0;

        len = httpd_req->content_len;
        buffer = malloc( len );

        if( httpd_req_recv( httpd_req, buffer, len ) )
        {
                printf( "%s\n", buffer );

                char **messages = usr_strsep( buffer, '&', &mlen );

                motor_instruction_exec( messages, mlen );

                usr_freestrs( messages, mlen );

                usr_send_response( "Ok", httpd_req );
        }

        return ESP_OK;
}

esp_err_t usr_send_response( char *resp, httpd_req_t *httpd_req )
{
        httpd_resp_set_status( httpd_req, "200 OK" );
        httpd_resp_set_type( httpd_req, "text/html" );
        httpd_resp_set_hdr( httpd_req, "Server", "esp_http_server" );
        httpd_resp_set_hdr( httpd_req, "Access-Control-Allow-Origin", "http://localhost" );

        /*printf( "%s %i", resp, strlen( resp ) );*/

        httpd_resp_send( httpd_req, resp, strlen( resp ) );

        return ESP_OK;
}

motor_cfg_t motor_get_cfg_from_post( char *post_data )
{
        motor_cfg_t motor_cfg;

        if( strcmp( post_data, "motor0=right" ) == 0 )
        {
                motor_cfg.motor0 = MOTOR_ROT_RIGHT;
        }
        else if( strcmp( post_data, "motor0=stop" ) == 0 )
        {
                motor_cfg.motor0 = MOTOR_ROT_STOP;
        }
        else if( strcmp( post_data, "motor0=left" ) == 0 )
        {
                motor_cfg.motor0 = MOTOR_ROT_LEFT;
        }
        else if( strcmp( post_data, "motor1=right" ) == 0 )
        {
                motor_cfg.motor1 = MOTOR_ROT_RIGHT;
        }
        else if( strcmp( post_data, "motor1=stop" ) == 0 )
        {
                motor_cfg.motor1 = MOTOR_ROT_STOP;
        }
        else if( strcmp( post_data, "motor1=left" ) == 0 )
        {
                motor_cfg.motor1 = MOTOR_ROT_LEFT;
        }

        return motor_cfg;
}

void usr_httpd_start( void *arg )
{
        server_config.stack_size = 1024*8;

        if( httpd_start( &server_instance, &server_config ) == ESP_OK )
        {
                httpd_register_uri_handler( server_instance, &root_uri_get );
                httpd_register_uri_handler( server_instance, &root_uri_post );
                ESP_LOGI( TAG, "HTTP Server started on port %i.", server_config.server_port );
        }
        else
        {
                ESP_LOGE( TAG, "Server fault." );
        }
}

void usr_httpd_stop( void *arg )
{
        if( server_instance != NULL )
        {
                httpd_stop( &server_instance );
        }
}
