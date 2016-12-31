
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define PATH_MAX 2500
#include "pb-lib-strings.c" 


int main( int argc, char *argv[])
{
    char myfile[PATH_MAX];
    FILE *fp; 
    char myline[PATH_MAX];
    char readline[PATH_MAX];
    char myfield1[PATH_MAX];
    char myfield2[PATH_MAX];
    strncpy( myfile , argv[1] , PATH_MAX );

    fp = fopen( myfile , "rb+");
    while(  !feof(fp)   ) {
        fgets( readline , PATH_MAX,  fp );
        if(  !feof(fp)   ) 
        {
            strncpy( myline, string_cut( readline, 6, strlen( string_removelf( readline )) ) , PATH_MAX );
            printf( "%s\n" , myline );
            printf( "Field1: '%s'\n" , string_remove_arrowfield1( myline ) );
            printf( "Field2: '%s'\n" , string_remove_arrowfield2( myline ) );
        }
    }
    fclose( fp );
 

    return 0;
}


