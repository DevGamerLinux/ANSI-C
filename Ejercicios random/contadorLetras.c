#include <stdio.h>
#include <string.h>

char * soliDatos() ;
void contador( char * ) ;

int main()
{
    char *vector ;
    vector = soliDatos() ;
    contador( vector ) ;

    return 0 ;
} /* fin main */

char * soliDatos()
{
    char *vector ;
    printf( "Ingrese una frase: " ) ;
    gets( vector ) ;
    return vector ;
} // fin soliDatos

void contador( char *vector )
{
    int minus = 0 , 
        mayus = 0 , 
        espacios = 0 ;

    for( int i = 0 ; i < strlen(vector) ; i++ )
    {
        if( (int)vector[i] >= 97 && (int)vector[i] <= 122 ) minus++ ;        
        else if( (int)vector[i] >= 65 && (int)vector[i] <= 90 ) mayus++ ;        
        else if( (int)vector[i] == 32 ) espacios++ ;         
    }

    printf( "Minusculas: %d , Mayusculas: %d , Espacios: %d\n" , minus , mayus , espacios ) ;
} // fin contador