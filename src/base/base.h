/*
 *    base.h    --    header for general base functionality
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 9, 2022.
 * 
 *    This file is part of the Chik game base.
 * 
 *    The base is the core of the game functionality.
 *    This contains all the wrapped engine functionality,
 *    making it easy to use.
 */
#ifndef BASE_BASE_H
#define BASE_BASE_H

#include "libchik.h"

#if USE_SDL
    #include <SDL2/SDL.h>
#endif /* USE_SDL  */

#include "model.h"
/*
 *    Declare function pointers for the base that are defined
 *    in the engine and need to be linked.
 */
extern u32 ( *engine_init )( const s8 *modules, ... );

extern void *( *engine_load_function )( const s8 *spName );



extern handle_t ( *vbuffer_create )( void *spVerts, u32 sSize, u32 sVStride, v_layout_t sLayout );

extern void ( *vbuffer_free )( handle_t sVBuffer );

extern handle_t ( *texture_create_from_file )( s8 *spPath, u32 sFormat );

extern void ( *texture_free )( handle_t sTex );

extern handle_t ( *mesh_create )( handle_t sVBuffer, handle_t sTex );

extern void ( *mesh_set_vertex_buffer )( handle_t sMesh, handle_t sVBuffer );

extern void ( *mesh_set_texture )( handle_t sMesh, handle_t sTex );

extern void ( *mesh_translate )( vec3_t sTranslation );

extern void ( *mesh_rotate )( vec3_t sRotation );

extern void ( *mesh_draw )( handle_t sMesh );

extern void ( *mesh_free )( handle_t sMesh );

extern mat4_t ( *get_camera_view )( handle_t sCamera );

extern void ( *draw_frame )( void );

extern handle_t ( *create_camera )( void );

extern void ( *set_camera_position )( handle_t sCamera, vec3_t sPosition );

extern void ( *set_camera_direction )( handle_t sCamera, vec2_t sDirection );

extern void ( *set_camera_fov )( handle_t sCamera, float sFov );

extern void ( *set_camera )( handle_t sCamera );

extern vec2_t ( *get_screen_size )( void );

#if USE_SDL
extern SDL_Window *( *get_window )( void );
#endif /* USE_SDL  */

/*
 *    Error checks a function load.
 *
 *    @param const s8 *    The name of the function to load.
 *    @param u32 *         Set this to 1 if the function is not found.
 * 
 *    @return void *       The function pointer, or NULL if it failed.
 *                         The function pointer is cast to the correct type.
 */
void *base_load_function( const s8 *spName, u32 *spError );

/*
 *    Initializes resources for below functions.
 *
 *    @param const s8 *    The modules to load.
 *    @param ...           The modules to load.
 *
 *    @return u32          Whether or not the initialization was successful.
 *                         1 = success, 0 = failure.
 */
u32 base_engine_init( const s8 *spModules, ... );

/*
 *    Frees resources for below functions.
 */
void base_free_engine_resources();

/*
 *    Updates the engine.
 */
void base_update_engine();

#endif /* HOBKNIGHTS_BASE_BASE_H  */