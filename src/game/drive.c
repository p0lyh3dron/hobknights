#include "drive.h"

#include <SDL2/SDL.h>

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
        gpTransform = gpDriveable = nullptr;
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

    /*
     *    This shouldn't be here.
     */
    SDL_Event e;

    switch ( gpDriveable->aMoveType ) {
        case DRIVE_NOCLIP: {
            SDL_PumpEvents();
            const char *keys = SDL_GetKeyboardState( NULL );
            if( keys[ SDL_SCANCODE_ESCAPE ] ) {
                gActive = 0;
            }
            if( keys[ SDL_SCANCODE_W ] ) {
                gpTransform->aPosition.z += 0.1f * cosf( gpTransform->aRotation.y );
                gpTransform->aPosition.x -= 0.1f * sinf( gpTransform->aRotation.y );
            }
            if( keys[ SDL_SCANCODE_S ] ) {
                gpTransform->aPosition.z -= 0.1f * cosf( gpTransform->aRotation.y );
                gpTransform->aPosition.x += 0.1f * sinf( gpTransform->aRotation.y );
            }
            if( keys[ SDL_SCANCODE_A ] ) {
                gpTransform->aPosition.x += 0.1f * cosf( gpTransform->aRotation.y );
                gpTransform->aPosition.z += 0.1f * sinf( gpTransform->aRotation.y );
            }
            if( keys[ SDL_SCANCODE_D ] ) {
                gpTransform->aPosition.x -= 0.1f * cosf( gpTransform->aRotation.y );
                gpTransform->aPosition.z -= 0.1f * sinf( gpTransform->aRotation.y );
            }
            if( keys[ SDL_SCANCODE_UP ] ) {
                gpTransform->aRotation.y += 0.1f;
            }
            if( keys[ SDL_SCANCODE_DOWN ] ) {
                gpTransform->aRotation.y -= 0.1f;
            }
            if( keys[ SDL_SCANCODE_LEFT ] ) {
                gpTransform->aRotation.x -= 0.1f;
            }
            if( keys[ SDL_SCANCODE_RIGHT ] ) {
                gpTransform->aRotation.x += 0.1f;
            }
            if( keys[ SDL_SCANCODE_SPACE ] ) {
                gpTransform->aPosition.y += 0.1f;
            }
            if( keys[ SDL_SCANCODE_LCTRL ] ) {
                gpTransform->aPosition.y -= 0.1f;
            }
            while ( SDL_PollEvent( &e ) ) {
                if ( e.type == SDL_MOUSEMOTION ) {
                    gpTransform->aRotation.y += ( float )e.motion.xrel / 500.f;
                    gpTransform->aRotation.x -= ( float )e.motion.yrel / 500.f;
                }
            }
            break;
        }
        /*
         *    Clip movement is not yet implemented.
         */
    }
}