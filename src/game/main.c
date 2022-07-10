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

#include "../base/base.h"
#include "game.h"

s32 gActive = 1;

s32 run( void ) {
    filesystem_add_search_path( "./hobknights/" );

    if ( !base_engine_init( "./bin/libchikengine.so", "./bin/libchikgfx.so", nullptr ) ) {
        log_fatal( "Unable to initialize the engine!\n" );
        return 0;
    }

    game_setup();

    while ( gActive ) {
        base_update_engine();
        game_update();
    }

    game_teardown();

    base_free_engine_resources();

    return 0;
}