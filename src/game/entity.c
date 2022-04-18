#include "entity.h"

entity_flag_e gEntityFlags[ MAX_ENTITIES ] = { 0 };

e_transform_t gTransforms[ MAX_ENTITIES ]  = { 0 };
e_driveable_t gDriveables[ MAX_ENTITIES ]  = { 0 };
e_camera_t    gCameras   [ MAX_ENTITIES ]  = { 0 };

/*
 *    Creates an entity.
 *
 *    @return u32    The entity id, 0 if failed.
 */
u32 entity_create() {
    u64 i;
    for( i = 0; i < MAX_ENTITIES; i++ ) {
        if( gEntityFlags[ i ] == ENTITY_NONE ) {
            gEntityFlags[ i ] = ENTITY_PRESENT;
            return i;
        }
    }
    return 0;
}

/*
 *    Adds a transform component to an entity.
 *
 *    @param u32         The entity id.
 *    @param vec3_t *    The position.
 *    @param vec2_t *    The rotation.
 *
 *    @return u32        1 if the component was added, 0 if not.
 */
u32 entity_add_transform( u32 sId, vec3_t *spPosition, vec2_t *spRotation ) {
    if( gEntityFlags[ sId ] == ENTITY_PRESENT ) {
        if ( spPosition != NULL && spRotation != NULL ) {
            gTransforms[ sId ].aPosition = *spPosition;
            gTransforms[ sId ].aRotation = *spRotation;
        }
        else {
            gTransforms[ sId ].aPosition = ( vec3_t ){ 0.0f, 0.0f, 0.0f };
            gTransforms[ sId ].aRotation = ( vec2_t ){ 0.0f, 0.0f };
        }
        gTransforms[ sId ].aId       = sId;
        return 1;
    }
    return 0;
}

/*
 *    Returns a transform component from an entity.
 *
 *    @param u32                 The entity id.
 *
 *    @return e_transform_t *    The transform component, NULL if not found.
 */
e_transform_t *entity_get_transform( u32 sId ) {
    if( gEntityFlags[ sId ] == ENTITY_PRESENT ) {
        return &gTransforms[ sId ];
    }
    return NULL;
}

/*
 *    Adds a driveable component to an entity.
 *
 *    @param u32                      The entity id.
 *    @param e_drivable_movetype_e *  The move type.
 * 
 *    @return u32                     1 if the component was added, 0 if not.
 */
u32 entity_add_driveable( u32 sId, e_drivable_movetype_e *spMoveType ) {
    if( gEntityFlags[ sId ] == ENTITY_PRESENT ) {
        if ( spMoveType != NULL ) {
            gDriveables[ sId ].aMoveType = *spMoveType;
        }
        else {
            gDriveables[ sId ].aMoveType = DRIVE_NOCLIP;
        }
        gDriveables[ sId ].aId       = sId;
        return 1;
    }
    return 0;
}

/*
 *    Returns a driveable component from an entity.
 *
 *    @param u32                 The entity id.
 *
 *    @return e_driveable_t *    The driveable component, NULL if not found.
 */
e_driveable_t *entity_get_driveable( u32 sId ) {
    if( gEntityFlags[ sId ] == ENTITY_PRESENT ) {
        return &gDriveables[ sId ];
    }
    return NULL;
}

/*
 *    Adds a camera component to an entity.
 *
 *    @param u32         The entity id.
 *    @param vec3_t *    The origin offset.
 *
 *    @return u32        1 if the component was added, 0 if not.
 */
u32 entity_add_camera( u32 sId, vec3_t *spOriginOffset ) {
    if( gEntityFlags[ sId ] == ENTITY_PRESENT ) {
        if ( spOriginOffset != NULL ) {
            gCameras[ sId ].aOriginOffset = *spOriginOffset;
        }
        else {
            gCameras[ sId ].aOriginOffset = ( vec3_t ){ 0.0f, 0.0f, 0.0f };
        }
        gCameras[ sId ].aId           = sId;
        return 1;
    }
    return 0;
}

/*
 *    Returns a camera component from an entity.
 *
 *    @param u32         The entity id.
 *
 *    @return e_camera_t *    The camera component, NULL if not found.
 */
e_camera_t *entity_get_camera( u32 sId ) {
    if( gEntityFlags[ sId ] == ENTITY_PRESENT ) {
        return &gCameras[ sId ];
    }
    return NULL;
}

/*
 *    Removes an entity.
 *
 *    @param u32    The entity id.
 */
void entity_remove( u32 sId ) {
    gEntityFlags[ sId ] = ENTITY_NONE;
}