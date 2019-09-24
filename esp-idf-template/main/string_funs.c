#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "defs.h"

char** usr_strsep( char *str, char sep, int *item_count )
{
        int countSubStr = 0;
        int counter = 0;
        char **resp = NULL;

        while( 1 )
        {
                char i = *( str + counter );
                counter++;

                if( i == '&' )
                {
                        countSubStr++;
                }
                else if( i == '\0' )
                {
                        break;
                }
        }

        countSubStr++;

        resp = (char**)malloc( sizeof( char* ) * countSubStr );

        for( int i = 0; i < countSubStr; i++ )
        {
                if( ( i + 1 ) == countSubStr )
                {
                        resp[i] = malloc( strlen( str )+1 );
                        /*printf( "%s; %i\n", str, strlen( str ) );*/
                        resp[i] = strcpy( resp[i], str );
                        break;
                }

                char *sub = strchr( str, sep );

                int nPos = sub - str;

                /*printf( "nPos: %i\n", nPos );*/

                resp[i] = (char*)malloc( nPos+1 );

                resp[i] = strncpy( resp[i], str, nPos );

                str = str + nPos + 1;
                /*printf( "%s\n", str );*/
        }

        if( item_count != NULL )
        {
                *item_count = countSubStr;
        }

        printf( "Hey\n" );
        return resp;
}

void usr_freestrs( char **strs, int item_count )
{
        for( int i = 0; i < item_count; i++ )
        {
                free( strs[i] );
        }

        free( strs );
}
