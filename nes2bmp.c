
/*
  ########################################################
  ############ Fuzzy Rename and Cover Fetcher ############
  ########################################################

Requirements:
  1. gcc and linux (can be easily ported to Windows)
  2. here the first argument must and shall be the database.txt
  3. roms into dir roms/ (with .nes)
  4. covers into snaps/ (with .png) 
  5. target dir 

  "target" dir will be the folder with all bmp files (resized 300%)
*/


#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
//#include <unistd.h>
#include <string.h>
// for fexist
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

//#define PATH_MAX 2500
#include "pb-lib-strings.c" 
#include "pb-lib-functions.c" 




    static int compare_fun( const void *p, const void *q){
      const char *l = p ; 
      const char *r = q ; 
      int cmp; 
      cmp = strcmp( l, r );
      return cmp; 
    }


int fexist(char *a_option){
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}




int main( int argc, char *argv[])
{
    /// here the first argument must and shall be the database.txt
    char myfile[PATH_MAX];
    FILE *fp; 
    FILE *fp1; 
    FILE *fp2; 
    char myline[PATH_MAX];
    char readline[PATH_MAX];
    char myfield1[PATH_MAX];
    char myfield2[PATH_MAX];
    strncpy( myfile , argv[1] , PATH_MAX );


    fp2 = fopen( "listfound.lst" , "wb+");
    fclose( fp2 );

    /// couper les lignes fichiers en deux colonnes
    fp = fopen( myfile , "rb+");
    while(  !feof(fp)   ) {
        fgets( readline , PATH_MAX,  fp );
        if(  !feof(fp)   ) 
        {


            strncpy( myline, string_cut( readline, 6, strlen( string_removelf( readline )) ) , PATH_MAX );
            printf( "myline: '%s'\n" , myline );
            //printf( "Field1: '%s'\n" , string_remove_arrowfield1( myline ) );
            //printf( "Field2: '%s'\n" , string_remove_arrowfield2( myline ) );
            printf( "Field1b: '%s'\n" , string_remove_arrowfield1b( myline ) );
            printf( "Field2b: '%s'\n" , string_remove_arrowfield2b( myline ) );
            printf( "\n" );
        }
    }
    fclose( fp );


    /// list files into idata array
    char idata[5000][250];
    long filemax = 0;
    long n=0;
    DIR *dirp;
    struct dirent *dp;
    char line[PATH_MAX];
    printf( "----------------- \n" );
    printf( ": LOADING FILES : ... \n" );
    printf( "----------------- \n" );
    n = 0 ; 
    filemax = 0; 
    dirp = opendir( "." );
    while  ((dp = readdir( dirp )) != NULL  &&  
             n < sizeof idata / sizeof idata[ 0 ]) 
    {

        strncpy( line , dp->d_name , 250 );

        if ( strcmp( dp->d_name, "." ) != 0 ) 
        if ( strcmp( dp->d_name, ".." ) != 0 ) 
        if ( strstr( line, ".nes" ) != 0 )
        {
            strncpy( idata[ n++ ] , dp->d_name , 250 );
            filemax++;
            printf( " Loaded file to list: '%s'\n", dp->d_name );
        } 
    }
    closedir( dirp );




    printf( "----------------- \n" );
    printf( ": SORTING FILES : ... \n" );
    printf( "----------------- \n" );
    if ( n > 1 )
      qsort( idata, n , sizeof idata[0], compare_fun );

    for( n = 1 ; n <= filemax ; n++)
       printf( " -List sorted : %d => %s \n" , n , idata[ n ] );


    ///////////////////
    // prepare directories
    if ( ( fexist( "snaps" ) != 2 ) || ( fexist( "target"  ) != 2 )  )
        system( " mkdir snaps target roms " ); 


    ///////////////////
    char filesourcesnap[PATH_MAX];
    char filetargetsnap[PATH_MAX];
    printf( "----------------- \n" );
    printf( ": SEARCH PNGs   : ... \n" );
    printf( "----------------- \n" );
    int coverpngfound = 0; 
    char readlinetmp[PATH_MAX];

    for( n = 0 ; n <= filemax-1 ; n++)
    {
     printf( "->Probing filename with db: %d => %s \n" , n , idata[ n ] );
     coverpngfound = 0; 

     fp = fopen( myfile , "rb+");
     while(  !feof(fp)   ) {
        strncpy( readline, "", PATH_MAX );
        strncpy( readline, "", PATH_MAX );
        strncpy( myline, "", PATH_MAX );
        strncpy( myfield1, "", PATH_MAX );
        strncpy( myfield2, "", PATH_MAX );

        printf( "*READ*\n" );
        fgets( readlinetmp , PATH_MAX,  fp );
	strncpy( readline, string_removelf( readlinetmp ), PATH_MAX );

        if ( strcmp( readline, "" ) != 0 )
        if ( coverpngfound == 0 )
        if(  !feof(fp)   ) 
        {

              // verbose
              //printf( "readline: '%s'\n" ,  readline );
              strncpy( myline, string_removelf( string_cut( readline, 6, strlen( readline ) ) ) , PATH_MAX );
              //printf( "myline: '%s'\n" ,  myline );


              strncpy( myfield1 , string_removelf( string_remove_arrowfield1b( myline )) , PATH_MAX );
              //printf( "Field1: '%s'\n" , myfield1 );


              strncpy( myfield2 , string_removelf( string_remove_arrowfield2b( myline )) , PATH_MAX );
              //printf( "Field2: '%s'\n" , myfield2 );

              printf( "%d: %s/%s  %s \n", n, myfield1 , myfield2 , readline );

	     if ( strstr( idata[ n ], myfield1 ) != 0 ) 
	     //if ( strcmp( string_replace2( idata[ n ], ".nes" , "" ) , myfield1 ) == 0 ) 
	     {

              strncpy( filesourcesnap , "snaps/" , PATH_MAX );
              strncat( filesourcesnap , string_removelf( myfield2 ) , PATH_MAX - strlen( filesourcesnap ) -1 );
              strncat( filesourcesnap , ".png"  , PATH_MAX - strlen( filesourcesnap ) -1 );



              // fexist copying
	      if ( strcmp( filesourcesnap , "" ) != 0 ) 
              if ( fexist( filesourcesnap ) == 1 )
              {

              strncpy( filetargetsnap , "target/" , PATH_MAX );
              strncat( filetargetsnap , string_removelf( myfield1 ) , PATH_MAX - strlen( filetargetsnap ) -1 );
              strncat( filetargetsnap , ".bmp" , PATH_MAX - strlen( filetargetsnap ) -1 );

                printf( "FC:|%s| |%s|",  filetargetsnap, filesourcesnap );
                //linuxcopy( filetargetsnap, filesourcesnap );
                linuximgconvert( filetargetsnap, filesourcesnap );
		coverpngfound = 1; 
                coverpngfound = 1;
              }
	     }
        }
     }
     fclose( fp );
    } 


    printf("-nes2bmp completed -\n");
    return 0;
}


