#include <stdio.h>

int soliNumero( char * );
int mayor( int , int ) ;
int menor( int , int ) ;
int sumatoria( int , int );

int main()
{
    char *msj ;
    int val1 = 0 , 
        val2 = 0 ;

    msj = "Ingrese primer valor: " ;
    val1 = soliNumero( msj ) ;

    msj = "Ingrese segundo valor: " ;
    val2 = soliNumero( msj ) ;

    printf( "La sumatoria es %d." , sumatoria( val1 , val2 ) ) ;
    
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

int sumatoria( int x , int y )
{
    int suma = 0 ;

    for( int i = menor( x , y ) ; i <= mayor( x , y ) ; i++ )
    {
        suma += i ;
    }

    return suma ;
} // fin sumatoria