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
#include "drive.h"

s32 gActive = 1;

u32 gPlayer = 0;

static chik_vertex_t gVertices[ 3 ] = {
    { { -1.f, -1.f, 0.f }, { 1.0f, 0.f, 0.f, 1.0f } },
    { {  1.f, -1.f, 0.f }, { 1.0f, 1.f, 0.f, 1.0f } },
    { {  0.f,  1.f, 0.f }, { 1.0f, 0.f, 1.f, 1.0f } }
};

s32 run( void ) {
#if USE_SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        log_error( "Failed to initialize SDL.\n" );
        return 0;
    }
    SDL_SetRelativeMouseMode( SDL_TRUE );
#endif /* USE_SDL  */

    if ( !framework_init() ) {
        log_error( "Failed to initialize framework.\n" );
        framework_shutdown();
        return 0;
    }

    if ( !engine_init( "./bin/libchikgfx.so", nullptr ) ) {
        log_fatal( "Unable to initialize the engine!" );
        return 0;
    }

    gPlayer = entity_create();
    entity_add_transform( gPlayer, nullptr, nullptr );
    entity_add_driveable( gPlayer, nullptr );
    entity_add_camera( gPlayer, nullptr );

    e_transform_t *pPosition = entity_get_transform( gPlayer );
    e_driveable_t *pDrive    = entity_get_driveable( gPlayer );
    e_camera_t    *pCamera   = entity_get_camera( gPlayer );

    pCamera->aOriginOffset.y = 10.f;

    drive_set_driven_entity( gPlayer );

    /*
     *    Starts a new frame.
     */
    void ( *stat_start_frame )() = engine_load_function( "stat_start_frame" );

    handle_t handle = create_vertex_buffer( gVertices, 3 );
    handle_t camera = create_camera();

    set_camera( camera );

    while ( gActive ) {
        if ( stat_start_frame ) {
            stat_start_frame();
        }
#if USE_SDL
    
    vec2_t res          = get_screen_size();
    SDL_Window *pWindow = get_window();
    SDL_WarpMouseInWindow( pWindow, res.x / 2, res.y / 2 );
    
#endif /* USE_SDL  */
        drive_drive_driven_entity();

        draw_vertex_buffer( handle );

        vec3_t cam = ( vec3_t ){ 
            pPosition->aPosition.x + pCamera->aOriginOffset.x, 
            pPosition->aPosition.y + pCamera->aOriginOffset.y, 
            pPosition->aPosition.z + pCamera->aOriginOffset.z 
        };

        set_camera_position( camera, cam );
        set_camera_direction( camera, pPosition->aRotation );

        draw_frame();

        SDL_Delay( 1000 / 144 );
    }

#if USE_SDL
    SDL_Quit();
#endif /* USE_SDL  */

    framework_shutdown();

    return 0;
}