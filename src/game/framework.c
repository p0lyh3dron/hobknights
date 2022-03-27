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
 *    @param vec3_t    The first point of the triangle.
 *    @param vec3_t    The second point of the triangle.
 *    @param vec3_t    The third point of the triangle.
 */
void ( *draw_triangle )( vec3_t a, vec3_t b, vec3_t c ) = 0;
/*
 *    Creates a camera.
 *
 *    @return handle_t          The handle to the camera.
 */
handle_t ( *create_camera )( void ) = 0;

/*
 *    Sets camera position.
 *
 *    @param handle_t           The handle to the camera.
 *    @param vec3_t             The position of the camera.
 */
void ( *set_camera_position )( handle_t sCamera, vec3_t sPosition ) = 0;
/*
 *    Sets camera direction.
 *
 *    @param handle_t           The handle to the camera.
 *    @param vec2_t             The direction of the camera.
 */
void ( *set_camera_direction )( handle_t sCamera, vec2_t sDirection ) = 0;

/*
 *    Sets camera FOV.
 *
 *    @param handle_t           The handle to the camera.
 *    @param float              The FOV of the camera.
 */
void ( *set_camera_fov )( handle_t sCamera, float sFov ) = 0;

/*
 *    Sets the global camera.
 *
 *    @param handle_t           The handle to the camera.
 */
void ( *set_camera )( handle_t sCamera ) = 0;


/*
 *    Returns the width and height of the screen.
 *
 *    @return vec2_t             The width and height of the screen.
 */
vec2_t ( *get_screen_size )( void ) = 0;

/*
 *    Returns the SDL window.
 *
 *    @return SDL_Window *        The SDL window.
 */
SDL_Window *( *get_window )( void ) = 0;
/*
 *    Creates a vertex buffer.
 *
 *    @param chik_vertex_t *    The array of vertices to store in the buffer.
 *    @param u32                The number of vertices in the array.
 * 
 *    @return handle_t          The handle to the vertex buffer.
 */
handle_t ( *create_vertex_buffer )( chik_vertex_t *spVertices, u32 sCount );

/*
 *    Draws a vertex buffer.
 *
 *    @param handle_t          The handle to the vertex buffer.
 */
void ( *draw_vertex_buffer )( handle_t sBuffer );

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

    create_vertex_buffer = dl_sym( pGfx, "create_vertex_buffer" );
    if ( !create_vertex_buffer ) {
        log_error( "Failed to load create_vertex_buffer function.\n" );
        return 0;
    }

    draw_vertex_buffer = dl_sym( pGfx, "draw_vertex_buffer" );
    if ( !draw_vertex_buffer ) {
        log_error( "Failed to load draw_vertex_buffer function.\n" );
        return 0;
    }

    create_camera = dl_sym( pGfx, "create_camera" );
    if ( !create_camera ) {
        log_error( "Failed to load create_camera function.\n" );
        return 0;
    }

    set_camera_position = dl_sym( pGfx, "set_camera_position" );
    if ( !set_camera_position ) {
        log_error( "Failed to load set_camera_position function.\n" );
        return 0;
    }

    set_camera_direction = dl_sym( pGfx, "set_camera_direction" );
    if ( !set_camera_direction ) {
        log_error( "Failed to load set_camera_direction function.\n" );
        return 0;
    }

    set_camera_fov = dl_sym( pGfx, "set_camera_fov" );
    if ( !set_camera_fov ) {
        log_error( "Failed to load set_camera_fov function.\n" );
        return 0;
    }

    set_camera = dl_sym( pGfx, "set_camera" );
    if ( !set_camera ) {
        log_error( "Failed to load set_camera function.\n" );
        return 0;
    }

    get_screen_size = dl_sym( pGfx, "get_screen_size" );
    if ( !get_screen_size ) {
        log_error( "Failed to load get_screen_size function.\n" );
        return 0;
    }

    get_window = dl_sym( pGfx, "get_window" );
    if ( !get_window ) {
        log_error( "Failed to load get_window function.\n" );
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