/*
 *    framework.c    --    source file for declaring framework functions
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 * 
 *    This file is temporary as it is currently used for
 *    testing engine functionality, however the engine is
 *    currently in a very early stage of development.
 */
#include "framework.h"

/*
 *    Draws the current frame.
 */
void ( *draw_frame )( void ) = 0;
/*
 *    Draws a triangle to the screen.
 *
 *    @param chik_vec2_t    The first point of the triangle.
 *    @param chik_vec2_t    The second point of the triangle.
 *    @param chik_vec2_t    The third point of the triangle.
 */
void ( *draw_triangle )( chik_vec2_t a, chik_vec2_t b, chik_vec2_t c ) = 0;

dl_handle_t pGfx = 0;

/*
 *    Initialize all functions used in the engine.
 *
 *    @return s32    1 on success, 0 on failure
 */
s32 framework_init( void ) {
    pGfx = dl_open( "./bin/libchikgfx.so" );
    if( !pGfx ) {
        log_error( "Failed to load graphics library.\n" );
        return 0;
    }

    draw_frame    = dl_sym( pGfx, "draw_frame" );
    if ( !draw_frame ) {
        log_error( "Failed to load draw_frame function.\n" );
        return 0;
    }

    draw_triangle = dl_sym( pGfx, "draw_triangle" );
    if ( !draw_triangle ) {
        log_error( "Failed to load draw_triangle function.\n" );
        return 0;
    }

    return 1;
}

/*
 *    Shutdown all functions used in the engine.
 */
void framework_shutdown( void ) {
    if( pGfx ) {
        dl_close( pGfx );
    }
}