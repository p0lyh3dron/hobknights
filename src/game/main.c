/*
 *    main.c    --    source for main.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file defines the entry point for Hobknights.
 */
#include "libchik.h"

#define PLAYERSPEED 1

#include <math.h>
#include <string.h>

#if USE_SDL
#include <SDL2/SDL.h>
#endif /* USE_SDL  */

#include "framework.h"

#define FAST_OBJ_IMPLEMENTATION

#include "fast_obj.h"

static s32 gActive = 1;

handle_t load_obj( const s8 *spPath ) {
    fastObjMesh *pMesh = fast_obj_read( spPath );
    if ( pMesh == NULL ) {
        return 0;
    }
    chik_vertex_t *pVerts = ( chik_vertex_t * )malloc( pMesh->position_count * 3 * sizeof( chik_vertex_t ) );
    if ( pVerts == NULL ) {
        fast_obj_free( pMesh );
        return 0;
    }
    for ( u32 i = 0; i < pMesh->position_count; i++ ) {
        pVerts[ i ].aPos.x = pMesh->positions[ i * 3 + 0 ];
        pVerts[ i ].aPos.y = pMesh->positions[ i * 3 + 1 ];
        pVerts[ i ].aPos.z = pMesh->positions[ i * 3 + 2 ];

        //pVerts[ i ].aColor = ( color32_t ){ rand() % 255, rand() % 255, rand() % 255, 255 };
    }
    handle_t h = create_vertex_buffer( pVerts, pMesh->position_count );
    fast_obj_destroy( pMesh );

    return h;
}

static chik_vertex_t gVertices[ 3 ] = {
    { { -1.f, -1.f, 0.f }, { 1.0f, 0,    0,    1.0f } },
    { {  1.f, -1.f, 0.f }, { 0,    1.0f, 0,    1.0f } },
    { {  0.f,  1.f, 0.f }, { 0,    0,    1.0f, 1.0f } }
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

    //handle_t model = load_obj( "/home/karl/Desktop/Chocolate Engine/build/sidury/materials/models/riverhouse/riverhouse_source_scale.obj" );
    handle_t model = load_obj( "/home/karl/Desktop/Chocolate Engine/build/sidury/materials/models/protogen_wip_25d/protogen_wip_25d.obj" );

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
        position.z += 0.1f * cosf( direction.y ) * PLAYERSPEED;
        position.x -= 0.1f * sinf( direction.y ) * PLAYERSPEED;
    }
    if( keys[ SDL_SCANCODE_S ] ) {
        position.z -= 0.1f * cosf( direction.y ) * PLAYERSPEED;
        position.x += 0.1f * sinf( direction.y ) * PLAYERSPEED;
    }
    if( keys[ SDL_SCANCODE_A ] ) {
        position.x += 0.1f * cosf( direction.y ) * PLAYERSPEED;
        position.z += 0.1f * sinf( direction.y ) * PLAYERSPEED;
    }
    if( keys[ SDL_SCANCODE_D ] ) {
        position.x -= 0.1f * cosf( direction.y ) * PLAYERSPEED;
        position.z -= 0.1f * sinf( direction.y ) * PLAYERSPEED;
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
        position.y += 0.1f * PLAYERSPEED;
    }
    if( keys[ SDL_SCANCODE_LCTRL ] ) {
        position.y -= 0.1f * PLAYERSPEED;
    }
    SDL_Window *pWindow = get_window();
    u32 flags = SDL_GetWindowFlags( pWindow );
    if ( flags & SDL_WINDOW_INPUT_FOCUS ) {
        while ( SDL_PollEvent( &e ) ) {
        if ( e.type == SDL_MOUSEMOTION ) {
            direction.y += ( float )e.motion.xrel / 500.f;
            direction.x -= ( float )e.motion.yrel / 500.f;
        }
    }
        vec2_t res          = get_screen_size();
        set_camera_position( camera, position );
        set_camera_direction( camera, direction );
        
        SDL_WarpMouseInWindow( pWindow, res.x / 2, res.y / 2 );
        SDL_SetRelativeMouseMode( SDL_TRUE );
    }
    else {
        SDL_SetRelativeMouseMode( SDL_FALSE );
    }
    
#endif /* USE_SDL  */
        draw_vertex_buffer( handle );

        draw_frame();

        SDL_Delay( 1000 / 144 );
    }

#if USE_SDL
    SDL_Quit();
#endif /* USE_SDL  */

    framework_shutdown();

    return 0;
}