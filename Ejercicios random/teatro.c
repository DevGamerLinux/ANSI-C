#include <stdio.h>
#include <time.h>

typedef struct Calendario
{
    char* nombre ;  /* nombre del evento */
    time_t t ;      /* fecha y hora, documentacion: https://parzibyte.me/blog/2019/07/31/c-obtener-formatear-fecha-actual/#Struct_de_tipo_tm */
    char *grupo ;   /* artista o agrupacion */
    int precio ;    /* precio de entrada */
} eventos[30] ;     /* 30 registros disponibles */

/* pre-funciones o prototipos de funciones */
struct Calendario registrarEvento( struct Calendario ) ;    /* retorna nuevo evento */
time_t fechaHora() ;                                        /* retorna fecha y hora modificada */
void eliminarEvento( struct Calendario ) ;                  /* retorna eliminacion de un evento */
void mostrarEvento( struct Calendario ) ;                   /* muestra la informacion de un evento */

int main()
{
    return 0 ;
} /* fin main */

struct Calendario registrarEvento( struct Calendario evento ) 
{
    return evento ;
} /* fin registrarEvento */

time_t fechaHora() 
{
    time_t fecha ;
    return fecha ;
} /* fin fechaHora */

void eliminarEvento( struct Calendario evento )
{
} /* fin eliminarEvento */

void mostrarEvento( struct Calendario evento )
{} /* fin mostrarEvento */