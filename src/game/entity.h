#pragma once

#define MAX_ENTITIES 1024

typedef enum {
    ENTITY_NONE    = 0,
    ENTITY_PRESENT = 1 << 0,
} entity_flag_e;

#include "entitycomponents.h"

/*
 *    Creates an entity.
 *
 *    @return u32    The entity id, 0 if failed.
 */
u32 entity_create();

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
 *    Removes an entity.
 *
 *    @param u32    The entity id.
 */
void entity_remove( u32 sId );