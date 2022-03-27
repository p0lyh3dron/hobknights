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

#if USE_SDL
#include <SDL2/SDL.h>
#endif /* USE_SDL  */

#include "framework.h"

static s32 gActive = 1;

static chik_vertex_t gVertices[ 3 ] = {
    { { -1.f, -1.f, 0.f }, 1.f },
    { {  1.f, -1.f, 0.f }, 1.f },
    { {  0.f,  1.f, 0.f }, 1.f }
};

s32 run( void ) {
#if USE_SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        log_error( "Failed to initialize SDL.\n" );
        return 0;
    }
    SDL_SetRelativeMouseMode( SDL_TRUE );
    SDL_Event e;
#endif /* USE_SDL  */

    if ( !framework_init() ) {
        log_error( "Failed to initialize framework.\n" );
        framework_shutdown();
        return 0;
    }

    handle_t handle = create_vertex_buffer( gVertices, 3 );
    handle_t camera = create_camera();

    set_camera( camera );

    vec3_t position  = { 0.f, 0.f, -10.f };
    vec2_t direction = { 0.f, 0.f };

    while ( gActive ) {
#if USE_SDL
    SDL_PumpEvents();
    const char *keys = SDL_GetKeyboardState( NULL );
    if( keys[ SDL_SCANCODE_ESCAPE ] ) {
        gActive = 0;
    }
    if( keys[ SDL_SCANCODE_W ] ) {
        position.z += 0.1f * cosf( direction.y );
        position.x -= 0.1f * sinf( direction.y );
    }
    if( keys[ SDL_SCANCODE_S ] ) {
        position.z -= 0.1f * cosf( direction.y );
        position.x += 0.1f * sinf( direction.y );
    }
    if( keys[ SDL_SCANCODE_A ] ) {
        position.x += 0.1f * cosf( direction.y );
        position.z += 0.1f * sinf( direction.y );
    }
    if( keys[ SDL_SCANCODE_D ] ) {
        position.x -= 0.1f * cosf( direction.y );
        position.z -= 0.1f * sinf( direction.y );
    }
    if( keys[ SDL_SCANCODE_UP ] ) {
        direction.y += 0.1f;
    }
    if( keys[ SDL_SCANCODE_DOWN ] ) {
        direction.y -= 0.1f;
    }
    if( keys[ SDL_SCANCODE_LEFT ] ) {
        direction.x -= 0.1f;
    }
    if( keys[ SDL_SCANCODE_RIGHT ] ) {
        direction.x += 0.1f;
    }
    if( keys[ SDL_SCANCODE_SPACE ] ) {
        position.y += 0.1f;
    }
    if( keys[ SDL_SCANCODE_LCTRL ] ) {
        position.y -= 0.1f;
    }
    while ( SDL_PollEvent( &e ) ) {
        if ( e.type == SDL_MOUSEMOTION ) {
            direction.y += ( float )e.motion.xrel / 500.f;
            direction.x -= ( float )e.motion.yrel / 500.f;
        }
    }
    vec2_t res          = get_screen_size();
    SDL_Window *pWindow = get_window();
    SDL_WarpMouseInWindow( pWindow, res.x / 2, res.y / 2 );
    
#endif /* USE_SDL  */
        draw_vertex_buffer( handle );

        set_camera_position( camera, position );
        set_camera_direction( camera, direction );

        draw_frame();

        log_note( "Directions: %f, %f\n", direction.x, direction.y );

        SDL_Delay( 1000 / 144 );
    }

#if USE_SDL
    SDL_Quit();
#endif /* USE_SDL  */

    framework_shutdown();

    return 0;
}