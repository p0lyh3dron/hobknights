#include "drive.h"

#include <string.h>

#define PLAYERSPEED 1

extern s32 gActive;

e_transform_t *gpTransform = nullptr;
e_driveable_t *gpDriveable = nullptr;

/*
 *    Sets the driven entity.
 *
 *    @param u32    The entity id.
 */
void drive_set_driven_entity( u32 sId ) {
    gpTransform = entity_get_transform( sId );
    gpDriveable = entity_get_driveable( sId );

    if ( !gpTransform || !gpDriveable ) {
        gpTransform = nullptr;
        gpDriveable = nullptr;
        log_error( "Entity is not transformable or drivable!\n" );
        return;
    }
}

/*
 *    Drives the driven entity.
 */
void drive_drive_driven_entity() {
    if ( !gpTransform || !gpDriveable ) {
        return;
    }
    switch ( gpDriveable->aMoveType ) {
        case DRIVE_NOCLIP: {
            s8 *pEvent = platform_get_event();
            while ( pEvent != nullptr ) {
                if ( strncmp( pEvent, "esc\0", 4 ) == 0 ) {
                    gActive = 0;
                }
                if ( strncmp( pEvent, "w\0", 2 ) == 0 ) {
                    gpTransform->aPosition.z += 0.1f * cosf( gpTransform->aRotation.y ) * PLAYERSPEED;
                    gpTransform->aPosition.x -= 0.1f * sinf( gpTransform->aRotation.y ) * PLAYERSPEED;
                    gpTransform->aPosition.y += 0.1f * sinf( gpTransform->aRotation.x ) * PLAYERSPEED;
                }
                if ( strncmp( pEvent, "a\0", 2 ) == 0 ) {
                    gpTransform->aPosition.x -= 0.1f * cosf( gpTransform->aRotation.y ) * PLAYERSPEED;
                    gpTransform->aPosition.z -= 0.1f * sinf( gpTransform->aRotation.y ) * PLAYERSPEED;
                }
                if ( strncmp( pEvent, "s\0", 2 ) == 0 ) {
                    gpTransform->aPosition.z -= 0.1f * cosf( gpTransform->aRotation.y ) * PLAYERSPEED;
                    gpTransform->aPosition.x += 0.1f * sinf( gpTransform->aRotation.y ) * PLAYERSPEED;
                    gpTransform->aPosition.y -= 0.1f * sinf( gpTransform->aRotation.x ) * PLAYERSPEED;
                }
                if ( strncmp( pEvent, "d\0", 2 ) == 0 ) {
                    gpTransform->aPosition.x += 0.1f * cosf( gpTransform->aRotation.y ) * PLAYERSPEED;
                    gpTransform->aPosition.z += 0.1f * sinf( gpTransform->aRotation.y ) * PLAYERSPEED;
                }
                if ( strncmp( pEvent, "space\0", 6 ) == 0 ) {
                    gpTransform->aPosition.y += 0.1f * PLAYERSPEED;
                }
                if ( strncmp( pEvent, "lctrl\0", 7 ) == 0 ) {
                    gpTransform->aPosition.y -= 0.1f * PLAYERSPEED;
                }
                pEvent = platform_get_event();
            }
            vec2u_t mouse = platform_get_joystick_event();
            gpTransform->aRotation.x -= ( float )mouse.y / 500.f;
            gpTransform->aRotation.y -= ( float )mouse.x / 500.f;
            
            gpTransform->aRotation.x = MAX( gpTransform->aRotation.x, -3.14159f / 2.f );
            gpTransform->aRotation.x = MIN( gpTransform->aRotation.x,  3.14159f / 2.f );
            break;
        }
        /*
         *    Clip movement is not yet implemented.
         */
    }
}