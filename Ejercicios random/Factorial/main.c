#include <stdio.h>

int soliNumero( char * );
int mayor( int , int ) ;
int menor( int , int ) ;
int factorial( int ) ;

int main()
{
    char *msj ;
    int val1 = 0 ,  /* almacena el primer valor */ 
        f1 = 0 ,    /* almacena el valor factorial del primer valor */
        val2 = 0 ,  /* almacena el segundo valor */
        f2 = 0 ;    /* almacena el valor factorial del segundo valor */

    msj = "Ingrese primer valor: " ;
    val1 = soliNumero( msj ) ;
    f1 = factorial( val1 ) ;

    msj = "Ingrese segundo valor: " ;
    val2 = soliNumero( msj ) ;
    f2 = factorial( val2 ) ;

    msj = "Factorial de %d => %d mayor a Factorial de %d => %d." ;

    if( val1 > val2 ) printf( msj , val1 , f1 , val2 , f2 ) ;
    else if( val2 > val1 ) printf( msj , val2 , f2 , val1 , f1 ) ;
    else printf( "Los valores de los factoriales son iguales." ) ;
    
    
    return 0 ;
} /* fin main */

int soliNumero( char *msj )
{
    int numero = 0 ;
    printf( "%s" , msj );
    scanf( "%d" , &numero ) ;
    return numero ;
} /* fin soliNumero */

int mayor( int x , int y )
{
    return x > y ? x : y ;
} /* fin mayor */

int menor( int x , int y )
{
    return x < y ? x : y ;
}/* fin menor */

int factorial( int x )
{
    return x == 0 ? 1 : x * factorial( x-1 ) ;
} /* fin factorial */