#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 7200
#define BACKLOG 2
#define MAXDATASIZE 1024

int abrirSocket( int );
struct sockaddr_in configSocketServer( struct sockaddr_in );
int bindServer( int , int , struct sockaddr_in );
int escucharServer( int , int , int );

int main()
{
    int socketServer , 
        socketCliente ,
        enlaceServer ,
        escuchaServer ,
        sin_size ;
    
    sin_size = sizeof( struct sockaddr_in );
    
    char buff[ MAXDATASIZE ] ;
    
    struct sockaddr_in server  ,
                       cliente ;    
    
    socketServer = abrirSocket( socketServer );
    if( socketServer == -1 )
    {
        perror( "Error en socket.\n" );
        exit( -1 );
    }
    printf( "Socket server: ok.\n" );
            
    server = configSocketServer( server );
    printf( "Configuracion server: ok.\n" );
    
    enlaceServer = bindServer( enlaceServer , socketServer , server );
    if( enlaceServer == -1 )
    {
        perror( "Error en el bind" );
        exit( -1 );
    }
    printf( "Bind: ok.\n" );
    
    escuchaServer = escucharServer( escuchaServer , socketServer , BACKLOG );
    if( escuchaServer == -1 )
    {
        perror( "Error en el listen" );
        exit( -1 );
    }
    printf( "Listen: ok.\n" );
    
    socketCliente = accept( escuchaServer , (struct sockaddr*)&cliente , &sin_size );
    if( socketCliente == -1 ) 
    {
        perror( "Error en accept.\n" );
        exit( -1 );
    }
    printf( "Accept: OK.\n" );
        
    close( socketCliente );
    close( socketServer );
    return 0;
} // fin del main


/**
 * 
 * @param fd
 * @return 
 */
int abrirSocket( int fd )
{
    /**
     * AF_INET = Address Format, Internet = IP Addresses
     * PF_INET = Packet Format, Internet = IP, TCP/IP or UDP/IP
     * 
     * domain: PF_INET => IPv4
     * type: SOCK_STREAM => conexion bidireccional confiable
     * protocol: 0 => dominio de comunicacion
     */
    fd = socket( AF_INET , SOCK_STREAM , 0 );
    // si existe algún error, devuelve -1
    if( fd == -1 ) {                  
        return -1;
    }
    
    return fd;
} // fin abrirSocket


/**
 * 
 * @param server
 * @return 
 */
struct sockaddr_in configSocketServer( struct sockaddr_in server )
{
    server.sin_family = AF_INET;
    server.sin_port = htons( PORT );
    server.sin_addr.s_addr = INADDR_ANY; 
    bzero( & ( server.sin_zero ) , 8 );
    return server;
} // fin configSocketServer


/**
 * 
 * @param enlaceServer
 * @param socketServer
 * @param server
 * @return 
 */
int bindServer( int enlaceServer , int socketServer , struct sockaddr_in server )
{
    enlaceServer = bind( socketServer , ( struct sockaddr* )&server , sizeof( struct sockaddr ) );
    if( enlaceServer == -1 ) 
    {
        return -1;
    }
    return enlaceServer;
} // fin bindServer


/**
 * 
 * @param escuchaServer
 * @param socketServer
 * @param enlaces
 * @return 
 */
int escucharServer( int escuchaServer , int socketServer , int enlaces )
{    
    escuchaServer = listen( socketServer , enlaces );
    if( escuchaServer == -1 ) 
    {
        return -1;
    }
    return escuchaServer;    
} // fin escucharServer