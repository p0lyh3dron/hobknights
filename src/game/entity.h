#pragma once

#define MAX_ENTITIES 1024

typedef enum {
    ENTITY_NONE    = 0,
    ENTITY_PRESENT = 1 << 0,
} entity_flag_e;

#include "../base/base.h"

#include "entitycomponents.h"

extern e_transform_t gTransforms[ MAX_ENTITIES ];
extern e_driveable_t gDriveables[ MAX_ENTITIES ];
extern e_camera_t    gCameras   [ MAX_ENTITIES ];
extern e_light_t     gLights    [ MAX_ENTITIES ];
extern e_model_t     gModels    [ MAX_ENTITIES ];

/*
 *    Sets up entity system.
 */
void entity_setup( void );

/*
 *    Creates an entity.
 *
 *    @return u32    The entity id, 0 if failed.
 */
u32 entity_create( void );

/*
 *    Adds a transform component to an entity.
 *
 *    @param u32         The entity id.
 *    @param vec3_t *    The position.
 *    @param vec2_t *    The rotation.
 *
 *    @return u32        1 if the component was added, 0 if not.
 */
u32 entity_add_transform( u32 sId, vec3_t *spPosition, vec2_t *spRotation );

/*
 *    Returns a transform component from an entity.
 *
 *    @param u32                 The entity id.
 *
 *    @return e_transform_t *    The transform component, NULL if not found.
 */
e_transform_t *entity_get_transform( u32 sId );

/*
 *    Adds a driveable component to an entity.
 *
 *    @param u32                      The entity id.
 *    @param e_drivable_movetype_e *  The move type.
 * 
 *    @return u32                     1 if the component was added, 0 if not.
 */
u32 entity_add_driveable( u32 sId, e_drivable_movetype_e *spMoveType );

/*
 *    Returns a driveable component from an entity.
 *
 *    @param u32                 The entity id.
 *
 *    @return e_driveable_t *    The driveable component, NULL if not found.
 */
e_driveable_t *entity_get_driveable( u32 sId );

/*
 *    Adds a camera component to an entity.
 *
 *    @param u32         The entity id.
 *    @param vec3_t *    The origin offset.
 *
 *    @return u32        1 if the component was added, 0 if not.
 */
u32 entity_add_camera( u32 sId, vec3_t *spOriginOffset );

/*
 *    Returns a camera component from an entity.
 *
 *    @param u32         The entity id.
 *
 *    @return e_camera_t *    The camera component, NULL if not found.
 */
e_camera_t *entity_get_camera( u32 sId );

/*
 *    Adds a light component to an entity.
 *
 *    @param u32         The entity id.
 *    @param vec3_t      The color.
 *    @param f32         The intensity.
 * 
 *    @return u32        1 if the component was added, 0 if not.
 */
u32 entity_add_light( u32 sId, vec3_t sColor, f32 sIntensity );

/*
 *    Returns a light component from an entity.
 *
 *    @param u32         The entity id.
 *
 *    @return e_light_t *    The light component, NULL if not found.
 */
e_light_t *entity_get_light( u32 sId );

/*
 *    Adds a model component to an entity.
 *
 *    @param u32         The entity id.
 *    @param model_t     The model.
 * 
 *    @return u32        1 if the component was added, 0 if not.
 */
u32 entity_add_model( u32 sId, model_t sModel );

/*
 *    Returns a model component from an entity.
 *
 *    @param u32         The entity id.
 *
 *    @return e_model_t *    The model component, NULL if not found.
 */
e_model_t *entity_get_model( u32 sId );

/*
 *    Removes an entity.
 *
 *    @param u32    The entity id.
 */
void entity_remove( u32 sId );

/*
 *    Updates all entities.
 */
void entity_update( void );