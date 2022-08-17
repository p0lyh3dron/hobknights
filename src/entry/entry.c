/*
 *    entry.c    --    entry point for Chik engine games.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This source file loads the client and server ( if networked ), 
 *    and then starts the game loop.
 */
#include "libchik.h"

#define PATH_MAX_LENGTH 1024

#include <string.h>

void print_help( void ) {
    const char *pExec = args_get_executable();

    printf( "Usage: %s [options]\n", pExec );
    printf( "Options ( '*' means required ):\n" );
    printf( "  -h, --help                 Print this help message.\n" );
    printf( "* -g, --game <game>          The game to run.\n" );
    printf( "  -c, --client               Run as a client.\n" );
    printf( "  -s, --server               Run as a server.\n" );
    printf( "  -n, --network              Run as a client or server.\n" );
    printf( "  -p, --port <port>          Set the port to use.\n" );
    printf( "  -l, --log  <logfile>       Set the log file to use.\n" );
    printf( "  -d, --debug                Enable debug mode.\n" );
    printf( "  -v, --version              Print the version of Chik.\n" );
}

/*
 *    Entry point for Chik engine games.
 *
 *    @param int        Number of arguments passed to the program.
 *    @param char **    Array of arguments passed to the program.
 *
 *    @return int       0 on success, 1 on failure.
 */
int main( const int argc, const char **argv ) {
    args_init( argc, argv );
    threadpool_init();
    filesystem_init( "./", "/", nullptr );
    log_open_file( "./log.txt" );

    dl_handle_t d      = 0;
    const char *pGame  = 0;

    if( args_has( "--help" ) ) {
        print_help();
        return 0;
    }

    /*
     *    Check for game parameter.
     */
    if( args_has( "-g" ) || args_has( "--game" ) ) {
        pGame = args_get_str( "-g" );

        if( pGame == NULL ) {
            pGame = args_get_str( "--game" );
        }

        if( pGame != NULL ) {
            char pPath[ PATH_MAX_LENGTH ];
            snprintf( pPath, PATH_MAX_LENGTH, "./%s/bin/lib%s%s", pGame, pGame, DL_EXTENSION );

            d = dl_open( pPath );
        }
    }
    else {
        log_fatal( "int main( const int, const char** ): No game specified.\n" );
    }

    /*
     *    dl_open() failed.
     */
    if ( d == 0 ) {
        log_fatal( "int main( const int, const char** ): Could not load game: %s.\n\ndl_error(): %s\n", pGame, dl_error() );
    }

    s32 ( *pRun )( void ) = 0;
    *( void** )( &pRun )  = dl_sym( d, "run" );

    /*
     *    dl_sym() failed.
     */
    if( pRun == 0 ) {
        log_fatal( "int main( const int, const char** ): Could not find run function in game: %s.\n\ndl_error(): %s\n", pGame, dl_error() );
    }

    s32 result = pRun();

    dl_close( d );
    log_close_file();

    return result;
}