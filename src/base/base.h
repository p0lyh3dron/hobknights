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

#include "model.h"
#include "shaderops.h"
#include "text.h"

/*
 *    Declare function pointers for the base that are defined
 *    in the engine and need to be linked.
 */
extern u32 ( *engine_init )( const s8 *modules, ... );

extern u32 ( *engine_update )( void );

extern void *( *engine_load_function )( const s8 *spName );

extern void ( *engine_free )();



extern trap_t ( *vbuffer_create )( void *spVerts, u32 sSize, u32 sVStride, v_layout_t sLayout );

extern void ( *vbuffer_free )( trap_t sVBuffer );

extern trap_t ( *texture_create_from_file )( s8 *spPath, u32 sFormat );

extern trap_t ( *text_create )( const s8 * );

extern void ( *texture_free )( trap_t sTex );

extern trap_t ( *mesh_create )( trap_t sVBuffer, trap_t sTex );

extern void ( *mesh_set_skip_projection )( trap_t sMesh );

extern void ( *mesh_set_skip_clipping )( trap_t sMesh );

extern void ( *mesh_set_vertex_buffer )( trap_t sMesh, trap_t sVBuffer );

extern void ( *mesh_set_texture )( trap_t sMesh, trap_t sTex );

extern void ( *mesh_translate )( vec3_t sTranslation );

extern void ( *mesh_rotate )( vec3_t sRotation );

extern void ( *mesh_scale )( vec3_t sScale );

extern void ( *mesh_draw )( trap_t sMesh );

extern void ( *mesh_free )( trap_t sMesh );

extern mat4_t ( *get_camera_view )( trap_t sCamera );

extern void ( *draw_frame )( void );

extern trap_t ( *create_camera )( void );

extern void ( *set_camera_position )( trap_t sCamera, vec3_t sPosition );

extern void ( *set_camera_direction )( trap_t sCamera, vec2_t sDirection );

extern void ( *set_camera_fov )( trap_t sCamera, float sFov );

extern void ( *set_camera )( trap_t sCamera );

extern vec2_t ( *get_screen_size )( void );



extern s8 *( *platform_get_event )( void );

extern vec2u_t ( *platform_get_joystick_event )( void );

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