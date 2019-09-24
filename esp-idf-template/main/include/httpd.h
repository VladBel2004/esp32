#include "freertos/FreeRTOS.h"
#include "esp_http_server.h"

#ifndef _USR_HTTPD
#define _USR_HTTPD


esp_err_t usr_httpd_root_get_handler( httpd_req_t *httpd_req );
esp_err_t usr_httpd_root_post_handler( httpd_req_t *httpd_req );

// Response sender
esp_err_t usr_send_response( char *resp, httpd_req_t *httpd_req );

// Post analisator
void usr_post_analisator( char **post_data );

httpd_uri_t root_uri_get = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = usr_httpd_root_get_handler,
        .user_ctx = NULL,
};

httpd_uri_t root_uri_post = {
        .uri = "/",
        .method = HTTP_POST,
        .handler = usr_httpd_root_post_handler,
        .user_ctx = NULL,
};

// Server config
httpd_config_t server_config = HTTPD_DEFAULT_CONFIG();

// Server instance
httpd_handle_t server_instance = NULL;

#endif
