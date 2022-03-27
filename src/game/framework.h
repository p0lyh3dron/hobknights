/*
 *    framework.h    --    header file for declaring framework functions
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 * 
 *    This file is temporary as it is currently used for
 *    testing engine functionality, however the engine is
 *    currently in a very early stage of development.
 */
#pragma once

#include "libchik.h"

#if USE_SDL
#include <SDL2/SDL.h>
#endif /* USE_SDL  */

/*
 *    Draws the current frame.
 */
extern void ( *draw_frame )( void );
/*
 *    Draws a triangle to the screen.
 *
 *    @param vec3_t    The first point of the triangle.
 *    @param vec3_t    The second point of the triangle.
 *    @param vec3_t    The third point of the triangle.
 */
extern void ( *draw_triangle )( vec3_t a, vec3_t b, vec3_t c );
/*
 *    Creates a camera.
 *
 *    @return handle_t          The handle to the camera.
 */
extern handle_t ( *create_camera )( void );

/*
 *    Sets camera position.
 *
 *    @param handle_t           The handle to the camera.
 *    @param vec3_t             The position of the camera.
 */
extern void ( *set_camera_position )( handle_t sCamera, vec3_t sPosition );
/*
 *    Sets camera direction.
 *
 *    @param handle_t           The handle to the camera.
 *    @param vec2_t             The direction of the camera.
 */
extern void ( *set_camera_direction )( handle_t sCamera, vec2_t sDirection );

/*
 *    Sets camera FOV.
 *
 *    @param handle_t           The handle to the camera.
 *    @param float              The FOV of the camera.
 */
extern void ( *set_camera_fov )( handle_t sCamera, float sFov );

/*
 *    Sets the global camera.
 *
 *    @param handle_t           The handle to the camera.
 */
extern void ( *set_camera )( handle_t sCamera );

/*
 *    Returns the width and height of the screen.
 *
 *    @return vec2_t             The width and height of the screen.
 */
extern vec2_t ( *get_screen_size )( void );

/*
 *    Returns the SDL window.
 *
 *    @return SDL_Window *        The SDL window.
 */
extern SDL_Window *( *get_window )( void );
/*
 *    Creates a vertex buffer.
 *
 *    @param chik_vertex_t *    The array of vertices to store in the buffer.
 *    @param u32                The number of vertices in the array.
 * 
 *    @return handle_t          The handle to the vertex buffer.
 */
extern handle_t ( *create_vertex_buffer )( chik_vertex_t *spVertices, u32 sCount );

/*
 *    Draws a vertex buffer.
 *
 *    @param handle_t          The handle to the vertex buffer.
 */
extern void ( *draw_vertex_buffer )( handle_t sBuffer );

/*
 *    Initialize all functions used in the engine.
 *
 *    @return s32    1 on success, 0 on failure
 */
s32 framework_init( void );

/*
 *    Shutdown all functions used in the engine.
 */
void framework_shutdown( void );