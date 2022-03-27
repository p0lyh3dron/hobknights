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

    vec3_t position  = { 0.f, 0.f, 0.f };
    vec2_t direction = { 0.f, 0.f };

    while ( gActive ) {
#if USE_SDL
        while ( SDL_PollEvent( &e ) ) {
            if ( e.type == SDL_QUIT ) {
                gActive = 0;
            }
            if ( e.type == SDL_KEYDOWN ) {
                if ( e.key.keysym.sym == SDLK_ESCAPE ) {
                    gActive = 0;
                }
                if ( e.key.keysym.sym == SDLK_UP ) {
                    direction.x -= 0.06f;
                }
                if ( e.key.keysym.sym == SDLK_DOWN ) {
                    direction.x += 0.06f;
                }
                if ( e.key.keysym.sym == SDLK_LEFT ) {
                    direction.y -= 0.06f;
                }
                if ( e.key.keysym.sym == SDLK_RIGHT ) {
                    direction.y += 0.06f;
                }

                if ( e.key.keysym.sym == SDLK_w ) {
                    position.z -= 1.f;
                }
                if ( e.key.keysym.sym == SDLK_s ) {
                    position.z += 1.f;
                }
                if ( e.key.keysym.sym == SDLK_a ) {
                    position.x -= 1.f;
                }
                if ( e.key.keysym.sym == SDLK_d ) {
                    position.x += 1.f;
                }

                if ( e.key.keysym.sym == SDLK_SPACE ) {
                    position.y += 1.f;
                }
                if ( e.key.keysym.sym == SDLK_LCTRL ) {
                    position.y -= 1.f;
                }
            }
        }
#endif /* USE_SDL  */
        draw_vertex_buffer( handle );

        set_camera_position( camera, position );
        set_camera_direction( camera, direction );

        draw_frame();

        SDL_Delay( 1000 / 144 );
    }

#if USE_SDL
    SDL_Quit();
#endif /* USE_SDL  */

    framework_shutdown();

    return 0;
}