#pragma once

#define MAX_ENTITIES 1024

typedef enum {
    ENTITY_NONE    = 0,
    ENTITY_PRESENT = 1 << 0,
} entity_flag_e;

#include "../base/base.h"

#include "entitycomponents.h"

extern entity_flag_e _entity_flags[MAX_ENTITIES];

extern e_transform_t _transforms[MAX_ENTITIES];
extern e_driveable_t _driveables[MAX_ENTITIES];
extern e_camera_t    _cameras[MAX_ENTITIES];
extern e_light_t     _lights[MAX_ENTITIES];
extern e_model_t     _models[MAX_ENTITIES];

/*
 *    Sets up entity system.
 */
void entity_setup(void);

/*
 *    Creates an entity.
 *
 *    @return unsigned int    The entity id, 0 if failed.
 */
unsigned int entity_create(void);

/*
 *    Adds a transform component to an entity.
 *
 *    @param unsigned int id        The entity id.
 *    @param vec3_t      *pos       The position.
 *    @param vec2_t      *rot       The rotation.
 *
 *    @return unsigned int        1 if the component was added, 0 if not.
 */
unsigned int entity_add_transform(unsigned int id, vec3_t *pos, vec2_t *rot);

/*
 *    Returns a transform component from an entity.
 *
 *    @param unsigned int id                The entity id.
 *
 *    @return e_transform_t *    The transform component, NULL if not found.
 */
e_transform_t *entity_get_transform(unsigned int id);

/*
 *    Adds a driveable component to an entity.
 *
 *    @param unsigned int           id         The entity id.
 *    @param e_drivable_movetype_e *move_type  The move type.
 *
 *    @return unsigned int                     1 if the component was added, 0 if not.
 */
unsigned int entity_add_driveable(unsigned int id, e_drivable_movetype_e *move_type);

/*
 *    Returns a driveable component from an entity.
 *
 *    @param unsigned int id                The entity id.
 *
 *    @return e_driveable_t *    The driveable component, NULL if not found.
 */
e_driveable_t *entity_get_driveable(unsigned int id);

/*
 *    Adds a camera component to an entity.
 *
 *    @param unsigned int id               The entity id.
 *    @param vec3_t      *origin_offset    The origin offset.
 *
 *    @return unsigned int        1 if the component was added, 0 if not.
 */
unsigned int entity_add_camera(unsigned int id, vec3_t *origin_offset);

/*
 *    Returns a camera component from an entity.
 *
 *    @param unsigned int id        The entity id.
 *
 *    @return e_camera_t *    The camera component, NULL if not found.
 */
e_camera_t *entity_get_camera(unsigned int id);

/*
 *    Adds a light component to an entity.
 *
 *    @param unsigned int id         The entity id.
 *    @param vec3_t       color      The color.
 *    @param float        intensity  The intensity.
 *
 *    @return unsigned int        1 if the component was added, 0 if not.
 */
unsigned int entity_add_light(unsigned int id, vec3_t color, float intensity);

/*
 *    Returns a light component from an entity.
 *
 *    @param unsigned int id        The entity id.
 *
 *    @return e_light_t *    The light component, NULL if not found.
 */
e_light_t *entity_get_light(unsigned int id);

/*
 *    Adds a model component to an entity.
 *
 *    @param unsigned int id            The entity id.
 *    @param model_t     *model         The model.
 *
 *    @return unsigned int        1 if the component was added, 0 if not.
 */
unsigned int entity_add_model(unsigned int id, model_t *model);

/*
 *    Returns a model component from an entity.
 *
 *    @param unsigned int id        The entity id.
 *
 *    @return e_model_t *    The model component, NULL if not found.
 */
e_model_t *entity_get_model(unsigned int id);

/*
 *    Removes an entity.
 *
 *    @param unsigned int id   The entity id.
 */
void entity_remove(unsigned int id);

/*
 *    Updates all entities.
 */
void entity_update(void);