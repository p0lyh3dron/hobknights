/*
 *    main.c    --    source for main.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file defines the entry point for Hobknights.
 */
#include "libchik.h"

#include <math.h>
#include <string.h>
#include <assert.h>

#if USE_SDL
#include <SDL2/SDL.h>
#endif /* USE_SDL  */

#include "../base/base.h"
#include "game.h"

s32 gActive = 1;

s32 run( void ) {
    filesystem_add_search_path( "./hobknights/" );
#if USE_SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        log_error( "Failed to initialize SDL.\n" );
        return 0;
    }
    SDL_SetRelativeMouseMode( SDL_TRUE );
#endif /* USE_SDL  */

    if ( !base_engine_init( "./bin/libchikengine.so", "./bin/libchikgfx.so", nullptr ) ) {
        log_fatal( "Unable to initialize the engine!\n" );
        return 0;
    }

    game_setup();

    while ( gActive ) {
        game_update();
        SDL_Delay( 1000 / 144 );
    }

    game_teardown();

#if USE_SDL
    SDL_Quit();
#endif /* USE_SDL  */

    return 0;
}