/*
 *    base.c    --    source for general base functionality
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 9, 2022.
 * 
 *    This file is part of the Chik game base.
 * 
 *    The base is the core of the game functionality.
 *    This contains all the definitions for the base.
 */
#include "libchik.h"

#include "base.h"

/*
 *    Nullifys the function pointers.
 */
u32 ( *engine_init )( const s8 *modules, ... ) = 0;

u32 ( *engine_update )( void ) = 0;

void *( *engine_load_function )( const s8 *spName ) = 0;

void ( *engine_free )() = 0;



handle_t ( *vbuffer_create )( void *spVerts, u32 sSize, u32 sVStride, v_layout_t sLayout ) = 0;

void ( *vbuffer_free )( handle_t sVBuffer ) = 0;

handle_t ( *texture_create_from_file )( s8 *spPath, u32 sFormat ) = 0;

handle_t ( *text_create )( const s8 * ) = 0;

void ( *texture_free )( handle_t sTex ) = 0;

handle_t ( *mesh_create )( handle_t sVBuffer, handle_t sTex ) = 0;

void ( *mesh_set_skip_projection )( handle_t sMesh ) = 0;

void ( *mesh_set_skip_clipping )( handle_t sMesh ) = 0;

void ( *mesh_set_vertex_buffer )( handle_t sMesh, handle_t sVBuffer ) = 0;

void ( *mesh_set_texture )( handle_t sMesh, handle_t sTex ) = 0;

void ( *mesh_translate )( vec3_t sTranslation ) = 0;

void ( *mesh_rotate )( vec3_t sRotation ) = 0;

void ( *mesh_scale )( vec3_t sScale ) = 0;

void ( *mesh_draw )( handle_t sMesh ) = 0;

void ( *mesh_free )( handle_t sMesh ) = 0;

mat4_t ( *get_camera_view )( handle_t sCamera ) = 0;

void ( *draw_frame )( void ) = 0;

handle_t ( *create_camera )( void ) = 0;

void ( *set_camera_position )( handle_t sCamera, vec3_t sPosition ) = 0;

void ( *set_camera_direction )( handle_t sCamera, vec2_t sDirection ) = 0;

void ( *set_camera_fov )( handle_t sCamera, float sFov ) = 0;

void ( *set_camera )( handle_t sCamera ) = 0;

vec2_t ( *get_screen_size )( void ) = 0;




s8 *( *platform_get_event )( void ) = 0;

vec2u_t ( *platform_get_joystick_event )( void ) = 0;

/*
 *    Error checks a function load.
 *
 *    @param const s8 *    The name of the function to load.
 *    @param u32 *         Set this to 1 if the function is not found.
 * 
 *    @return void *       The function pointer, or NULL if it failed.
 *                         The function pointer is cast to the correct type.
 */
void *base_load_function( const s8 *spName, u32 *spError ) {
    void *pRet = nullptr;
    if ( ( pRet = engine_load_function( spName ) ) == nullptr ) {
        log_error( "Could not load function %s.\n", spName );
        *spError = 1;
        return nullptr;
    }
    return pRet;
}

/*
 *    Initializes resources for below functions.
 *
 *    @param const s8 *    The modules to load.
 *    @param ...           The modules to load.
 *
 *    @return u32          Whether or not the initialization was successful.
 *                         1 = success, 0 = failure.
 */
u32 base_engine_init( const s8 *spModules, ... ) {
    dl_handle_t engine = dl_open( "./bin/libchikengine.so" );
    if ( engine == nullptr ) {
        log_error( "Could not load engine library.\n" );
        return 0;
    }

    *( void** )( &engine_init )          = dl_sym( engine, "engine_init" );
    *( void** )( &engine_update )        = dl_sym( engine, "engine_update" );
    *( void** )( &engine_load_function ) = dl_sym( engine, "engine_load_function" );
    *( void** )( &engine_free )          = dl_sym( engine, "engine_free" );

    if ( engine_init == nullptr ) {
        log_error( "u32 base_engine_init( const s8 *, ... ) Could not find engine_init function.\n" );
        return 0;
    }
    if ( engine_update == nullptr ) {
        log_error( "u32 base_engine_init( const s8 *, ... ) Could not find engine_update function.\n" );
        return 0;
    }
    if ( engine_load_function == nullptr ) {
        log_error( "u32 base_engine_init( const s8 *, ... ) Could not find engine_load_function function.\n" );
        return 0;
    }
    if ( engine_free == nullptr ) {
        log_error( "u32 base_engine_init( const s8 *, ... ) Could not find engine_free function.\n" );
        return 0;
    }

    if ( !engine_init( "./bin/libchikengine.so", "./bin/libchikplatform.so", "./bin/libchikaudio.so", "./bin/libchikgfx.so", nullptr ) ) {
        log_error( "u32 base_engine_init( const s8 *, ... ) Could not initialize engine.\n" );
        return 0;
    }

    u32 error = 0;

    *( void** )( &vbuffer_create )              = base_load_function( "vbuffer_create", &error );
    *( void** )( &vbuffer_free )                = base_load_function( "vbuffer_free", &error );
    *( void** )( &texture_create_from_file )    = base_load_function( "texture_create_from_file", &error );
    *( void** )( &text_create )                 = base_load_function( "text_create", &error );
    *( void** )( &texture_free )                = base_load_function( "texture_free", &error );
    *( void** )( &mesh_create )                 = base_load_function( "mesh_create", &error );
    *( void** )( &mesh_set_skip_projection )    = base_load_function( "mesh_set_skip_projection", &error );
    *( void** )( &mesh_set_skip_clipping )      = base_load_function( "mesh_set_skip_clipping", &error );
    *( void** )( &mesh_set_vertex_buffer )      = base_load_function( "mesh_set_vertex_buffer", &error );
    *( void** )( &mesh_set_texture )            = base_load_function( "mesh_set_texture", &error );
    *( void** )( &mesh_translate )              = base_load_function( "mesh_translate", &error );
    *( void** )( &mesh_rotate )                 = base_load_function( "mesh_rotate", &error );
    *( void** )( &mesh_scale )                  = base_load_function( "mesh_scale", &error );
    *( void** )( &mesh_draw )                   = base_load_function( "mesh_draw", &error );
    *( void** )( &mesh_free )                   = base_load_function( "mesh_free", &error );
    *( void** )( &get_camera_view )             = base_load_function( "get_camera_view", &error );
    *( void** )( &draw_frame )                  = base_load_function( "draw_frame", &error );
    *( void** )( &create_camera )               = base_load_function( "create_camera", &error );
    *( void** )( &set_camera_position )         = base_load_function( "set_camera_position", &error );
    *( void** )( &set_camera_direction )        = base_load_function( "set_camera_direction", &error );
    *( void** )( &set_camera_fov )              = base_load_function( "set_camera_fov", &error );
    *( void** )( &set_camera )                  = base_load_function( "set_camera", &error );
    *( void** )( &get_screen_size )             = base_load_function( "get_screen_size", &error );

    *( void** )( &platform_get_event )          = base_load_function( "platform_get_event", &error );
    *( void** )( &platform_get_joystick_event ) = base_load_function( "platform_get_joystick_event", &error );

    return !error;
}

/*
 *    Frees resources for below functions.
 */
void base_free_engine_resources() {
    engine_free();
}

/*
 *    Updates the engine.
 */
void base_update_engine() {
    engine_update();
}
