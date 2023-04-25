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

unsigned int _active = 0;

/*
 *    Nullifys the function pointers.
 */
unsigned int (*engine_init)(const char *modules, ...) = 0;

unsigned int (*engine_update)(void) = 0;

void *(*engine_load_function)(const char *spName) = 0;

void (*engine_free)() = 0;

long (*stat_get_time_diff)() = 0;

image_t *(*image_create_from_file)(char *, unsigned int) = 0;

image_t *(*text_create)(const char *) = 0;

void *(*vbuffer_create)(void *, unsigned int, unsigned int, v_layout_t) = 0;

void (*vbuffer_free)(void *) = 0;

void *(*mesh_create)(void *) = 0;

void (*mesh_set_vbuffer)(void *, void *) = 0;

void (*mesh_append_asset)(void *, void *, unsigned long) = 0;

void (*mesh_set_asset)(void *, void *, unsigned long, unsigned long);

void *(*mesh_get_asset)(void *, unsigned long);

void (*mesh_draw)(void *) = 0;

void (*mesh_free)(void *) = 0;

mat4_t (*get_camera_view)(void *);

void (*draw_frame)(void) = 0;

void *(*create_camera)(void);

void (*set_camera_position)(void *, vec3_t);

void (*set_camera_direction)(void *, vec2_t);

void (*set_camera_fov)(void *, float);

void (*set_camera)(void *);

vec2_t (*get_screen_size)(void) = 0;

void (*begin_render_group)(void);

char *(*platform_get_event)(void) = 0;

vec2u_t (*platform_get_joystick_event)(void) = 0;

/*
 *    Error checks a function load.
 *
 *    @param const char *name     The name of the function to load.
 *    @param unsigned int *error         Set this to 1 if the function is not found.
 *
 *    @return void *       The function pointer, or NULL if it failed.
 *                         The function pointer is cast to the correct type.
 */
void *base_load_function(const char *name, unsigned int *error) {
    void *ret = nullptr;

    if ((ret = engine_load_function(name)) == nullptr) {
        VLOGF_ERR("Could not load function %s.\n", name);
        *error = 1;
        return nullptr;
    }

    return ret;
}

/*
 *    Quits the application.
 */
void quit() { _active = 0; }

/*
 *    Initializes resources for below functions.
 *
 *    @param const char *modules    The modules to load.
 *    @param ...                  The modules to load.
 *
 *    @return unsigned int          Whether or not the initialization was successful.
 *                         1 = success, 0 = failure.
 */
unsigned int base_engine_init(const char *modules, ...) {
    shell_command_t commands[] = {{"quit", "Quits the application.", quit},
                                  {nullptr, nullptr, nullptr}};
    shell_register_commands(commands);

    dl_handle_t engine = dl_open("./bin/libchikengine" DL_EXTENSION);
    if (engine == nullptr) {
        LOGF_ERR("unsigned int base_engine_init( const char *, ... ): Could not load "
                 "engine library.\n");
        return 0;
    }

    *(void **)(&engine_init)          = dl_sym(engine, "engine_init");
    *(void **)(&engine_update)        = dl_sym(engine, "engine_update");
    *(void **)(&engine_load_function) = dl_sym(engine, "engine_load_function");
    *(void **)(&engine_free)          = dl_sym(engine, "engine_free");

    if (engine_init == nullptr) {
        LOGF_ERR("unsigned int base_engine_init( const char *, ... ): Could not find "
                 "engine_init function.\n");
        return 0;
    }
    if (engine_update == nullptr) {
        LOGF_ERR("unsigned int base_engine_init( const char *, ... ): Could not find "
                 "engine_update function.\n");
        return 0;
    }
    if (engine_load_function == nullptr) {
        LOGF_ERR("unsigned int base_engine_init( const char *, ... ): Could not find "
                 "engine_load_function function.\n");
        return 0;
    }
    if (engine_free == nullptr) {
        LOGF_ERR("unsigned int base_engine_init( const char *, ... ): Could not find "
                 "engine_free function.\n");
        return 0;
    }

    if (!engine_init("./bin/libchikengine" DL_EXTENSION,
                     "./bin/libchikplatform" DL_EXTENSION,
                     "./bin/libchikaudio" DL_EXTENSION,
                     "./bin/libchikgfx" DL_EXTENSION, nullptr)) {
        LOGF_ERR("unsigned int base_engine_init( const char *, ... ): Could not "
                 "initialize engine.\n");
        return 0;
    }

    unsigned int error = 0;

    *(void **)(&stat_get_time_diff) = base_load_function("stat_get_time_diff", &error);

    *(void **)(&image_create_from_file) = base_load_function("image_create_from_file", &error);
    *(void **)(&text_create)            = base_load_function("text_create", &error);
    *(void **)(&vbuffer_create)         = base_load_function("vbuffer_create", &error);
    *(void **)(&vbuffer_free)           = base_load_function("vbuffer_free", &error);
    *(void **)(&mesh_create)            = base_load_function("mesh_create", &error);
    *(void **)(&mesh_set_vbuffer)       = base_load_function("mesh_set_vbuffer", &error);
    *(void **)(&mesh_append_asset)      = base_load_function("mesh_append_asset", &error);
    *(void **)(&mesh_get_asset)         = base_load_function("mesh_get_asset", &error);
    *(void **)(&mesh_set_asset)         = base_load_function("mesh_set_asset", &error);
    *(void **)(&mesh_draw)              = base_load_function("mesh_draw", &error);
    *(void **)(&mesh_free)              = base_load_function("mesh_free", &error);
    *(void **)(&get_camera_view)        = base_load_function("get_camera_view", &error);
    *(void **)(&draw_frame)             = base_load_function("draw_frame", &error);
    *(void **)(&create_camera)          = base_load_function("create_camera", &error);
    *(void **)(&set_camera_position)    = base_load_function("set_camera_position", &error);
    *(void **)(&set_camera_direction)   = base_load_function("set_camera_direction", &error);
    *(void **)(&set_camera_fov)         = base_load_function("set_camera_fov", &error);
    *(void **)(&set_camera)             = base_load_function("set_camera", &error);
    *(void **)(&get_screen_size)        = base_load_function("get_screen_size", &error);
    *(void **)(&begin_render_group)     = base_load_function("begin_render_group", &error);

    *(void **)(&platform_get_event)          = base_load_function("platform_get_event", &error);
    *(void **)(&platform_get_joystick_event) = base_load_function("platform_get_joystick_event", &error);

    _active = 1;

    return !error;
}

/*
 *    Updates the engine and checks the game state.
 *
 *    @return unsigned int          Whether or not the game is still running.
 */
unsigned int base_engine_update(void) { return engine_update() && _active; }

/*
 *    Returns the delta time between frames in seconds.
 *
 *    @return float      The delta time.
 */
float base_get_dt(void) { return stat_get_time_diff() / 1000000.f; }

/*
 *    Frees resources for below functions.
 */
void base_free_engine_resources() { engine_free(); }

/*
 *    Updates the engine.
 */
void base_update_engine() { engine_update(); }