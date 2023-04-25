#include "drive.h"

#include <string.h>

#define PLAYERSPEED 1

extern int _active;

e_transform_t *_trans = nullptr;
e_driveable_t *_drive = nullptr;

/*
 *    Sets the driven entity.
 *
 *    @param unsigned int    The entity id.
 */
void drive_set_driven_entity(unsigned int sId) {
    _trans = entity_get_transform(sId);
    _drive = entity_get_driveable(sId);

    if (!_trans || !_drive) {
        _trans = nullptr;
        _drive = nullptr;
        log_error("Entity is not transformable or drivable!\n");
        return;
    }
}

/*
 *    Drives the driven entity.
 */
void drive_drive_driven_entity() {
    if (!_trans || !_drive) {
        return;
    }
    switch (_drive->move_type) {
    case DRIVE_NOCLIP: {
        char *pEvent = platform_get_event();
        while (pEvent != nullptr) {
            if (strncmp(pEvent, "esc\0", 4) == 0) {
                _active = 0;
            }
            if (strncmp(pEvent, "w\0", 2) == 0) {
                _trans->pos.z +=
                    0.1f * cosf(_trans->rot.y) *
                    cosf(_trans->rot.x) * PLAYERSPEED;
                _trans->pos.x -=
                    0.1f * sinf(_trans->rot.y) *
                    cosf(_trans->rot.x) * PLAYERSPEED;
                _trans->pos.y +=
                    0.1f * sinf(_trans->rot.x) * PLAYERSPEED;
            }
            if (strncmp(pEvent, "a\0", 2) == 0) {
                _trans->pos.x -=
                    0.1f * cosf(_trans->rot.y) * PLAYERSPEED;
                _trans->pos.z -=
                    0.1f * sinf(_trans->rot.y) * PLAYERSPEED;
            }
            if (strncmp(pEvent, "s\0", 2) == 0) {
                _trans->pos.z -=
                    0.1f * cosf(_trans->rot.y) *
                    cosf(_trans->rot.x) * PLAYERSPEED;
                _trans->pos.x +=
                    0.1f * sinf(_trans->rot.y) *
                    cosf(_trans->rot.x) * PLAYERSPEED;
                _trans->pos.y -=
                    0.1f * sinf(_trans->rot.x) * PLAYERSPEED;
            }
            if (strncmp(pEvent, "d\0", 2) == 0) {
                _trans->pos.x +=
                    0.1f * cosf(_trans->rot.y) * PLAYERSPEED;
                _trans->pos.z +=
                    0.1f * sinf(_trans->rot.y) * PLAYERSPEED;
            }
            if (strncmp(pEvent, "space\0", 6) == 0) {
                _trans->pos.y += 0.1f * PLAYERSPEED;
            }
            if (strncmp(pEvent, "lctrl\0", 7) == 0) {
                _trans->pos.y -= 0.1f * PLAYERSPEED;
            }
            pEvent = platform_get_event();
        }
        vec2u_t mouse = platform_get_joystick_event();
        _trans->rot.x -= (float)mouse.y / 500.f;
        _trans->rot.y -= (float)mouse.x / 500.f;

        _trans->rot.x =
            MAX(_trans->rot.x, -3.14159f / 2.f);
        _trans->rot.x =
            MIN(_trans->rot.x, 3.14159f / 2.f);
        break;
    }
        /*
         *    Clip movement is not yet implemented.
         */
    }
}