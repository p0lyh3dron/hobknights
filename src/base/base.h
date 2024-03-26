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
#include "types.h"
#include "collision.h"

/*
 *    Declare function pointers for the base that are defined
 *    in the engine and need to be linked.
 */
extern unsigned int (*engine_init)(const char *modules, ...);

extern unsigned int (*engine_update)(void);

extern void *(*engine_load_function)(const char *spName);

extern void (*engine_free)();

extern long (*stat_get_time_diff)();

extern image_t *(*image_create_from_file)(char *, unsigned int);

extern image_t *(*text_create)(const char *);

extern void *(*vbuffer_create)(void *, unsigned int, unsigned int, v_layout_t);

extern void (*vbuffer_free)(void *);

extern void *(*mesh_create)(void *);

extern void (*mesh_set_vbuffer)(void *, void *);

extern void (*mesh_append_asset)(void *, void *, unsigned long);

extern void (*mesh_set_asset)(void *, void *, unsigned long, unsigned long);

extern void *(*mesh_get_asset)(void *, unsigned long);

extern void (*mesh_draw)(void *);

extern void (*mesh_free)(void *);

extern mat4_t (*get_camera_view)(void *);

extern void (*draw_frame)(void);

extern void *(*create_camera)(void);

extern void (*set_camera_position)(void *, vec3_t);

extern void (*set_camera_direction)(void *, vec2_t);

extern void (*set_camera_fov)(void *, float);

extern void (*set_camera)(void *);

extern vec2_t (*get_screen_size)(void);

extern void *(*rendertarget_get_backbuffer)(void);

extern void (*begin_render_group)(void);

extern char *(*platform_get_event)(void);

extern vec2u_t (*platform_get_joystick_event)(void);



extern void *(*audio_create_from_file)(const char *path, unsigned int loop);

extern unsigned int (*audio_play)(void *audio);

extern unsigned int (*audio_stop)(void *audio);

extern unsigned int (*audio_set_listener_position)(void *, vec3_t, vec3_t, vec2_t);

/*
 *    Error checks a function load.
 *
 *    @param const char *name     The name of the function to load.
 *    @param unsigned int *error         Set this to 1 if the function is not found.
 *
 *    @return void *       The function pointer, or NULL if it failed.
 *                         The function pointer is cast to the correct type.
 */
void *base_load_function(const char *name, unsigned int *error);

/*
 *    Initializes resources for below functions.
 *
 *    @param const char *modules    The modules to load.
 *    @param ...                  The modules to load.
 *
 *    @return unsigned int          Whether or not the initialization was successful.
 *                         1 = success, 0 = failure.
 */
unsigned int base_engine_init(const char *modules, ...);

/*
 *    Updates the engine and checks the game state.
 *
 *    @return unsigned int          Whether or not the game is still running.
 */
unsigned int base_engine_update(void);

/*
 *    Returns the delta time between frames in seconds.
 *
 *    @return float      The delta time.
 */
float base_get_dt(void);

/*
 *    Frees resources for below functions.
 */
void base_free_engine_resources();

/*
 *    Updates the engine.
 */
void base_update_engine();

#endif /* HOBKNIGHTS_BASE_BASE_H  */