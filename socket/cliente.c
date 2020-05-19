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
#define IPSERVER "127.0.0.1" /* IP del servidor */
#define SIZEDATA 1024   /* tamaño de transmision de datos */
#define h_addr h_addr_list[0] /* for backward compatibility */
#define length(x) ( sizeof(x) / sizeof( (x)[0] ) ) /* largo de un vector, retorna long */

/* prototipo de funciones o pre-funciones */
int menu( int );
int abrirSocket( int );
struct sockaddr_in configServer( struct sockaddr_in , int , struct hostent* ) ;
int contarLineas();
void largoCadena( int[] );
void buscarCadena( int , int , char* );
int contenidoFichero();

int main( int argc , char **argv )
{
    int op = 2 ,        /* almacena la opcion seleccionada por el usuario */ 
        socketCliente , /* socket del cliente */
        aux = 0 ,
        *vector ;       /* almacena las dimensiones de cada linea */

    char cadena[ SIZEDATA ] ;  
    
    struct sockaddr_in server ; /* estructura del servidor */
    struct hostent *he ;
    
    /*------------------------------------------------------------------------*/

    /**
     * argv recibe 3 argumentos.
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
    
    he = gethostbyname( IPSERVER ) ; /* asignamos puerto */
    if( he == NULL )
    {
        printf( "gethostbyname: error\n" ) ;
        exit( -1 ) ;
    }
    
    /*------------------------------------------------------------------------*/

    /**
     * @descripcion
     *  se abre socket para el cliente 
     */
    socketCliente = abrirSocket( socketCliente );
    if( socketCliente == -1 )
    {
        printf( "Socket cliente: error.\n" );
        exit( -1 );
    }
    
    /*------------------------------------------------------------------------*/
    
    /**
     * @descripcion
     *  se configura las variables del servidor
     */
    server = configServer( server , PORT , he );
    
    /*------------------------------------------------------------------------*/

    /**
     * @descripcion
     *  se realiza la vinculacion entre el socket del cliente y el servidor
     */
    if( connect( socketCliente , (struct sockaddr*)&server , sizeof( server ) ) < 0 )
    {       
        printf( "connect: error\n" );
        exit( -1 );
    } printf( "Conexion Exitosa.\n" );

    /*------------------------------------------------------------------------*/

    while( op != 0 )
    {
        op = menu( op ) ;
        if( op == 0 )
        {
            write( socketCliente , &op , sizeof(int) ) ;
            printf( "Cerrando cliente.\n" ) ;            
        }
        else if( op == 1 )
        {
            aux = contenidoFichero();            
            
            if( aux == 1 ) 
            {
                printf( "Fichero vacio, no se enviara nada.\n" );
            }
            else
            {
                printf( "Enviando peticion ...\n" );
                write( socketCliente , &op , sizeof(int) ) ;

                /* cantidad de lineas */
                op = contarLineas() ;
                write( socketCliente , &op , sizeof(int) ) ;                

                /* redimencionamos el vector a la cantidad de lineas */
                vector = (int*)malloc( op * sizeof(int) ) ;
                /* recibir dimension de lineas */
                largoCadena( vector );

                /* lineas a transferir */
                for( int i = 0 ; i < op ; i++)
                {
                    buscarCadena( aux , i , cadena );
                    write( socketCliente , &cadena , 1024 ) ;
                    aux += vector[i];
                }

                /* liberar memeoria del vector */
                free( vector );
            } /* fin enviando contenido del fichero */

        }
        else
        {
            printf( "Valor ingresado no valido.\n" );
        }
        
    }

    /*------------------------------------------------------------------------*/

    close( socketCliente ) ;
    return 0 ;
}

/**
 * @brief menu de opciones.
 * 
 * @param op 
 * @return int 
 */
int menu( int op )
{
    char *msj = "0.- Terminar conexion.\n1.- Trasmitir Fichero.\nop: ";
    printf( "%s" , msj );
    scanf( "%d" , &op );
    return op;
} /* fin menu */

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
} /* fin abrirSocket */

/**
 * @brief configuracion de la estructura del servidor
 * 
 * @param server 
 * @param puerto 
 * @param he 
 * @return struct sockaddr_in 
 */
struct sockaddr_in configServer( struct sockaddr_in server , int puerto , struct hostent *he )
{
    /* memset( &server , '0' , sizeof( server ) ); */
    bzero( (char*)&server , sizeof(server) ) ;
    server.sin_family = AF_INET;
    server.sin_port = htons( puerto ); 
    bcopy( (char*)he->h_addr , (char *)&server.sin_addr.s_addr , he->h_length ) ;    
    return server ;
} /* fin configServer */

/**
 * @brief cuenta la cantidad de lineas del fichero
 * 
 * @return dimension
 */
int contarLineas()
{
    FILE *leer = NULL;
    char *origen = "origen.txt" ;
    char caracteres[1024] ;
    int dimension = 0;

    leer = fopen( origen , "r" );

    while (feof(leer) == 0)
 	{
 	    fgets( caracteres , 100 , leer ) ;
        dimension++;
 	}//printf("\n");

    fclose(leer);
    return dimension;
} /* fin contarLineas */


/**
 * @brief cuenta la dimension de cada linea del fichero
 * 
 * @param vector 
 */
void largoCadena( int vector[] )
{
    FILE *leer = NULL;
    char *origen = "origen.txt" ;
    char caracteres[1024] ;
    int i = 0;

    leer = fopen( origen , "r" );

    while (feof(leer) == 0)
 	{
 	    fgets( caracteres , 100 , leer ) ;
        vector[i] =  (int) strlen( caracteres ) ;
        i++ ;
 	}

    fclose(leer);
} /* fin largoCadena */

/**
 * @brief devuelve la linea capturada del fichero
 * 
 * SEEK_SET -> Posición respecto al inicio del archivo
 * SEEK_CUR -> Incremento relativo a la posición actual
 * SEEK_END -> Posición respecto al final del archivo
 * 
 * @param caracteres
 * @param linea
 * @param cadena
 * 
 * @return cadena
*/
void buscarCadena( int caracteres , int linea , char* cadena )
{
    FILE *leer = NULL;
    char *origen = "origen.txt" ;

    leer = fopen( origen , "r" );

    switch( linea )
    {
        case 0:
            fseek( leer , caracteres , SEEK_SET );
            fgets( cadena , 1024 , leer ) ;
            break ;
        default:
            fseek( leer , caracteres , SEEK_CUR );
            fgets( cadena , 1024 , leer ) ;
            break ;
    }

    fclose(leer);
} /* fin buscarCadena */

/**
 * @brief comprueba si el contenido del fichero esta vacio,
 *  de encontrar vacio el fichero retornara 1, de lo
 *  contrario, retorna 0.
 * 
 * @return int 
 */
int contenidoFichero()
{
    FILE *leer = NULL;
    char *origen = "origen.txt" ;

    leer = fopen( origen , "r" ) ;

    fseek( leer , 0 , SEEK_END );
    if( ftell( leer ) == 0 )
    {
        fclose( leer );
        return 1 ;  /* fichero vacio */
    }
    else 
    {
        fclose( leer );
        return 0 ; /* fichero no vacio */
    }

} /* fin contenidoFichero */