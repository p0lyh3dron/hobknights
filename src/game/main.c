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

#if 1
#include <SDL2/SDL.h>
#endif /* USE_SDL  */

#include "framework.h"

static s32 gActive = 1;

static chik_vertex_t gVertices[ 3 ] = {
    { { -1.f, -1.f, 0.f }, { 0.f, 0.f } },
    { {  1.f, -1.f, 0.f }, { 1.f, 0.f } },
    { {  0.f,  1.f, 0.f }, { 0.5f, 1.f } }
};

s32 run( void ) {
    log_msg( "Hello, world!\n" );
    log_note( "This is a note.\n" );
    log_warn( "This is a warning.\n" );

#if 1
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

    float theta = 0.0f;

    mempool_t *pMempool = mempool_new( 1024 * 1024 );

    if( pMempool == 0 ) {
        log_error( "Failed to create memory pool.\n" );
        framework_shutdown();
        return 0;
    }

    char *pStr = mempool_alloc( pMempool, 64 );
    strcpy( pStr, "Hello, world!" );

    log_msg( "Allocated string: %s\n", pStr );

    resource_t *pResource = resource_new( 1024 * 1024 );

    if( pResource == 0 ) {
        log_error( "Failed to create resource manager.\n" );
        framework_shutdown();
        return 0;
    }

    handle_t resource = resource_add( pResource, pStr, strlen( pStr ) + 1 );

    if( resource == 0 ) {
        log_error( "Failed to add resource to resource manager.\n" );
        framework_shutdown();
        return 0;
    }

    char *pStr2 = resource_get( pResource, resource );

    if( pStr2 == 0 ) {
        log_error( "Failed to get resource from resource manager.\n" );
        framework_shutdown();
        return 0;
    }

    log_msg( "Retrieved string: %s\n", pStr2 );
    log_msg( "Resource size = %d\n", HANDLE_GET_SIZE( resource ) );

    mempool_destroy( pMempool );

    resource_destroy( pResource );

    handle_t handle = create_vertex_buffer( gVertices, 3 );
    handle_t camera = create_camera();

    set_camera_position( camera, ( vec3_t ){ 0.f, 0.f, -5.f } );
    set_camera( camera );

    vec3_t position  = { 0.f, 0.f, 0.f };
    vec2_t direction = { 0.f, 0.f };

    while ( gActive ) {
#if 1
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
        /*draw_triangle( ( vec2_t ){ cos( theta ) / 2, sin( theta ) / 2 }, 
                       ( vec2_t ){ cos( theta + 6.28 / 3 ) / 2, sin( theta + 6.28 / 3 ) / 2 }, 
                       ( vec2_t ){ cos( theta + 2 * 6.28 / 3 ) / 2, sin( theta + 2 * 6.28 / 3 ) / 2 } );*/
    
        /*draw_triangle( ( vec2_t ){ -.5, -.5 }, 
                       ( vec2_t ){ .5, -.5 }, 
                       ( vec2_t ){ 0, theta } );*/
        draw_vertex_buffer( handle );

        set_camera_position( camera, position );
        set_camera_direction( camera, direction );

        draw_frame();

        SDL_Delay( 1000 / 144 );
        theta += 0.01f;
        //log_note( "Theta: %f\n", theta );
    }

#if USE_SDL
    SDL_Quit();
#endif /* USE_SDL  */

    framework_shutdown();

    return 0;
}