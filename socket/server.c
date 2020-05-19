#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define PORT 5555       /* puerto de conexion */
#define CONEXIONES 2    /* cantidad de conexiones permitidas */
#define SIZEDATA 1024   /* tamaño de transmision de datos */

int abrirSocket( int );
struct sockaddr_in configServer( struct sockaddr_in , int );
void escribirFichero( char* );

int main( int argc , char **argv )
{
    int socketServer ,   /* socket del servidor */
        socketCliente ,  /* socket para comunicarse con el cliente */
        opcion = 2 ;
    
    char buffer[ SIZEDATA ] ;

    struct sockaddr_in server , /* estructura del servidor */
                       cliente ;

    socklen_t peticiones ;

    /*------------------------------------------------------------------------*/

    /**
     * argv recibe hasta 3 argumentos.
     *  1.- Nombre del programa.
     *  2.- IP donde se conectara.
     *  3.- Puerto de enlace
     * 
     *  En este caso, no recibe ningun argumento adicional, 
     *  solo el primero argumento.
     * 
     * argc = cantidad de argumentos recibidos.
     * argv = vector con los argumentos.
    */
    if( argc != 1 ) 
    {
        printf( "Solo se ejecuta el programa sin parametros agregados.\n" );
        exit( -1 ) ;
    }

    /*------------------------------------------------------------------------*/
    
    /**
     * @brief se abre socket para el cliente 
     */
    socketServer = abrirSocket( socketServer );
    if( socketServer == -1 )
    {
        printf( "Socket server: error.\n" );
        exit( -1 );
    }

    /*------------------------------------------------------------------------*/
    
    /**
     * @brief se configura las variables del servidor
     */
    server = configServer( server , PORT );
    
    /*------------------------------------------------------------------------*/
    
    /**
     * @brief verifica si los parametros del servidor son correctos
     */
    if( inet_pton( AF_INET , "127.0.0.1" , &server.sin_addr ) <= 0 )
    {
        printf( "inet_pton error occured\n" );
        exit( -1 );
    }
    
    /*------------------------------------------------------------------------*/
    
    bind( socketServer , ( struct sockaddr* ) &server , sizeof( server ) );
    
    /*------------------------------------------------------------------------*/
    
    listen( socketServer , CONEXIONES );

    /*------------------------------------------------------------------------*/

    peticiones = sizeof( cliente ) ; 
    socketCliente = accept( socketServer, (struct sockaddr *) &cliente, &peticiones ) ;
    if( socketCliente < 0 )
    { 
        printf( "ERROR en accept" ) ;
        exit( -1 ) ;
    }

    /*------------------------------------------------------------------------*/

    while( opcion != 0 )
    {
        printf( "Esperando solicitud del cliente.\n" );
        read( socketCliente , &opcion , sizeof(int) ) ;
        if( opcion == 0 )
        {
            printf( "Cerrando servidor.\n" ) ;            
        }
        else if( opcion == 1 )
        {
            printf( "Recibiendo cantidad de lineas.\n" );
            read( socketCliente , &opcion , sizeof(int) ); /* cantidad de lineas */

            for( int i = 0 ; i < opcion ; i++ )
            {
                read( socketCliente , buffer , 1024 ) ;
                escribirFichero( buffer );
            } escribirFichero( "\n" );

            printf( "Fichero traspasado exitosamente.\n" );
        }
        else
        {
            printf( "Peticion desconocida.\n" );
        }
        
    } /* fin while */

    /*------------------------------------------------------------------------*/
    
    close( socketCliente ) ;
    close( socketServer ) ;
    return 0 ;
} /* fin del main */

/**
 * AF_INET = Address Format, Internet = IP Addresses
 * PF_INET = Packet Format, Internet = IP, TCP/IP or UDP/IP
 * 
 * domain: PF_INET => IPv4
 * type: SOCK_STREAM => conexion bidireccional confiable
 * protocol: 0 => dominio de comunicacion
 * 
 * @brief abre un socket
 * 
 * @param socketCliente
 * @return 
 */
int abrirSocket( int socketCliente )
{    
    socketCliente = socket( AF_INET , SOCK_STREAM , 0 );
    return socketCliente;
} // fin abrirSocket

/**
 * @brief configuracion de la estructura del servidor
 * 
 * @param server 
 * @param puerto 
 * @return struct sockaddr_in 
 */
struct sockaddr_in configServer( struct sockaddr_in server , int puerto )
{
    /* memset( &server , '0' , sizeof( server ) ); */
    bzero( (char*)&server , sizeof(server) ) ;    
    server.sin_family = AF_INET;
    server.sin_port = htons( puerto ); 
    server.sin_addr.s_addr = htonl( INADDR_ANY ); 
    return server;
} /* fin configServer */

/**
 * @brief ingresa una cadena de caracteres al fichero
 * 
 * @param linea 
 */
void escribirFichero( char* linea )
{
    FILE *escribir = NULL;
    char *destino = "destino.txt" ;
    
    escribir = fopen( destino , "a" );
    fprintf( escribir , "%s" , linea ) ;        
    
    fflush( escribir );
    fclose( escribir );
} /* fin escribirFichero */