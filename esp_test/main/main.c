#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void gpio( void *params );
void wifi( void *arg );

int app_main( void )
{
        xTaskCreatePinnedToCore( gpio, "wifi", 8192, NULL, 1, NULL, tskNO_AFFINITY );
        printf( "Hello World!\n" );
        return 0;
}
