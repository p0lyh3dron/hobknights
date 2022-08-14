#include "entity.h"

entity_flag_e gEntityFlags[ MAX_ENTITIES ] = { 0 };

e_transform_t gTransforms[ MAX_ENTITIES ]  = { 0 };
e_driveable_t gDriveables[ MAX_ENTITIES ]  = { 0 };
e_camera_t    gCameras   [ MAX_ENTITIES ]  = { 0 };
e_light_t     gLights    [ MAX_ENTITIES ]  = { 0 };
e_model_t     gModels    [ MAX_ENTITIES ]  = { 0 };

/*
 *    Sets up entity system.
 */
void entity_setup( void ) {
    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        gEntityFlags[ i ]    = ENTITY_NONE;
        gTransforms[ i ].aId = -1;
        gDriveables[ i ].aId = -1;
        gCameras[ i ].aId    = -1;
        gLights[ i ].aId     = -1;
        gModels[ i ].aId     = -1;
    }
}

/*
 *    Creates an entity.
 *
 *    @return u32    The entity id, 0 if failed.
 */
u32 entity_create( void ) {
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
    if ( gEntityFlags[ sId ] != ENTITY_PRESENT ) {
        return 0;
    }

    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        if ( gTransforms[ i ].aId == -1 ) {
            gTransforms[ i ].aId       = sId;
            if ( spPosition == nullptr ) {
                gTransforms[ i ].aPosition = ( vec3_t ){ 0.f, 0.f, 0.f };
            }
            else {
                gTransforms[ i ].aPosition = *spPosition;
            }
            if ( spRotation == nullptr ) {
                gTransforms[ i ].aRotation = ( vec2_t ){ 0.f, 0.f };
            }
            else {
                gTransforms[ i ].aRotation = *spRotation;
            }
            gTransforms[ i ].aScale = ( vec3_t ){ 1.f, 1.f, 1.f };
            return 1;
        }
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
    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        if ( gTransforms[ i ].aId == sId ) {
            return &gTransforms[ i ];
        }
    }
    return nullptr;
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
    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        if ( gDriveables[ i ].aId == -1 ) {
            gDriveables[ i ].aId       = sId;
            if ( spMoveType == nullptr ) {
                gDriveables[ i ].aMoveType = DRIVE_NOCLIP;
            }
            else {
                gDriveables[ i ].aMoveType = *spMoveType;
            }
            return 1;
        }
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
    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        if ( gDriveables[ i ].aId == sId ) {
            return &gDriveables[ i ];
        }
    }
    return nullptr;
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
    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        if ( gCameras[ i ].aId == -1 ) {
            gCameras[ i ].aId       = sId;
            if ( spOriginOffset == nullptr ) {
                gCameras[ i ].aOriginOffset = ( vec3_t ){ 0.f, 0.f, 0.f };
            }
            else {
                gCameras[ i ].aOriginOffset = *spOriginOffset;
            }
            return 1;
        }
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
    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        if ( gCameras[ i ].aId == sId ) {
            return &gCameras[ i ];
        }
    }
    return nullptr;
}

/*
 *    Adds a light component to an entity.
 *
 *    @param u32         The entity id.
 *    @param vec3_t      The color.
 *    @param f32         The intensity.
 * 
 *    @return u32        1 if the component was added, 0 if not.
 */
u32 entity_add_light( u32 sId, vec3_t sColor, f32 sIntensity ) {
    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        if ( gLights[ i ].aId == -1 ) {
            gLights[ i ].aId        = sId;
            gLights[ i ].aColor     = sColor;
            gLights[ i ].aIntensity = sIntensity;
            return 1;
        }
    }
    return 0;
}

/*
 *    Returns a light component from an entity.
 *
 *    @param u32         The entity id.
 *
 *    @return e_light_t *    The light component, NULL if not found.
 */
e_light_t *entity_get_light( u32 sId ) {
    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        if ( gLights[ i ].aId == sId ) {
            return &gLights[ i ];
        }
    }
    return nullptr;
}

/*
 *    Adds a model component to an entity.
 *
 *    @param u32         The entity id.
 *    @param model_t     The model.
 * 
 *    @return u32        1 if the component was added, 0 if not.
 */
u32 entity_add_model( u32 sId, model_t sModel ) {
    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        if ( gModels[ i ].aId == -1 ) {
            gModels[ i ].aId       = sId;
            gModels[ i ].aModel    = sModel;
            return 1;
        }
    }
    return 0;
}

/*
 *    Returns a model component from an entity.
 *
 *    @param u32         The entity id.
 *
 *    @return e_model_t *    The model component, NULL if not found.
 */
e_model_t *entity_get_model( u32 sId ) {
    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        if ( gModels[ i ].aId == sId ) {
            return &gModels[ i ];
        }
    }
    return nullptr;
}

/*
 *    Removes an entity.
 *
 *    @param u32    The entity id.
 */
void entity_remove( u32 sId ) {
    gEntityFlags[ sId ] = ENTITY_NONE;
}

/*
 *    Updates all entities.
 */
void entity_update( void ) {
    s64 i;
    for ( i = 0; i < MAX_ENTITIES; i++ ) {
        if ( gEntityFlags[ i ] == ENTITY_PRESENT ) {
            e_model_t *pModel     = entity_get_model( i );
            e_transform_t *pTrans = entity_get_transform( i );
            if ( pModel != nullptr ) {
                if ( pTrans ) {
                    pModel->aModel.aPos   = pTrans->aPosition;
                    pModel->aModel.aRot   = ( vec3_t ){ pTrans->aRotation.x, pTrans->aRotation.y };
                    pModel->aModel.aScale = pTrans->aScale;
                }
                model_draw( &pModel->aModel );
            }
        }
    }
}