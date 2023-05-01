#include "drive.h"

#include <string.h>

#define PLAYERSPEED 60

extern int _active;

e_transform_t *_trans = nullptr;
e_driveable_t *_drive = nullptr;

unsigned char _grounded = 0;
unsigned char _noclip   = 0;

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
        char *pEvent = platform_get_event();
        while (pEvent != nullptr) {
            if (strncmp(pEvent, "esc\0", 4) == 0) {
                _active = 0;
            }
            if (strncmp(pEvent, "w\0", 2) == 0) {
                _drive->velocity.z +=
                    0.1f * cosf(_trans->rot.y) *
                    cosf(_trans->rot.x) * PLAYERSPEED * base_get_dt() * 1000;
                _drive->velocity.x -=
                    0.1f * sinf(_trans->rot.y) *
                    cosf(_trans->rot.x) * PLAYERSPEED * base_get_dt() * 1000;
                if (_drive->move_type == DRIVE_NOCLIP)
                    _trans->pos.y += 0.1f * sinf(_trans->rot.x) * PLAYERSPEED * base_get_dt() * 1000;
            }
            if (strncmp(pEvent, "a\0", 2) == 0) {
                _drive->velocity.x -=
                    0.1f * cosf(_trans->rot.y) * PLAYERSPEED * base_get_dt() * 1000;
                _drive->velocity.z -=
                    0.1f * sinf(_trans->rot.y) * PLAYERSPEED * base_get_dt() * 1000;
            }
            if (strncmp(pEvent, "s\0", 2) == 0) {
                _drive->velocity.z -=
                    0.1f * cosf(_trans->rot.y) *
                    cosf(_trans->rot.x) * PLAYERSPEED * base_get_dt() * 1000;
                _drive->velocity.x +=
                    0.1f * sinf(_trans->rot.y) *
                    cosf(_trans->rot.x) * PLAYERSPEED * base_get_dt() * 1000;
                if (_drive->move_type == DRIVE_NOCLIP)
                    _trans->pos.y -= 0.1f * sinf(_trans->rot.x) * PLAYERSPEED * base_get_dt() * 1000;
            }
            if (strncmp(pEvent, "d\0", 2) == 0) {
                _drive->velocity.x +=
                    0.1f * cosf(_trans->rot.y) * PLAYERSPEED * base_get_dt() * 1000;
                _drive->velocity.z +=
                    0.1f * sinf(_trans->rot.y) * PLAYERSPEED * base_get_dt() * 1000;
            }
            if (strncmp(pEvent, "v\0", 2) == 0) {
                if (_drive->move_type == DRIVE_NOCLIP && _noclip == 0) {
                    _drive->move_type = DRIVE_CLIP;
                }
                else if (_noclip == 0) {
                    _drive->move_type = DRIVE_NOCLIP;

                    _drive->velocity.x = 0.f;
                    _drive->velocity.y = 0.f;
                    _drive->velocity.z = 0.f;
                }

                _noclip = 1;
            } else {
                _noclip = 0;
            }
            if (strncmp(pEvent, "space\0", 6) == 0) {
                if (_drive->move_type == DRIVE_NOCLIP)
                    _trans->pos.y += 0.1f * PLAYERSPEED * base_get_dt() * 1000;
                else if (_grounded) {
                    _drive->velocity.y = 2.f;
                }
            }
            if (strncmp(pEvent, "lctrl\0", 7) == 0) {
                if (_drive->move_type == DRIVE_NOCLIP)
                    _trans->pos.y -= 0.1f * PLAYERSPEED * base_get_dt() * 1000;
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

        if (_drive->move_type == DRIVE_CLIP) {
            _drive->acceleration.y = -.981f;
        }
        else {
            _drive->acceleration.y = 0.f;
        }

        float speed = pow(_drive->velocity.x,2) + pow(_drive->velocity.z,2);
        if (speed > 2.5f) {
            _drive->velocity.x *= sqrtf(2.5f/speed);
            _drive->velocity.z *= sqrtf(2.5f/speed);
        }

        _drive->velocity.x += _drive->acceleration.x * base_get_dt() * 1000;
        _drive->velocity.y += _drive->acceleration.y * base_get_dt() * 1000;
        _drive->velocity.z += _drive->acceleration.z * base_get_dt() * 1000;

        _trans->pos.x += _drive->velocity.x * base_get_dt() * 1000;
        _trans->pos.y += _drive->velocity.y * base_get_dt() * 1000;
        _trans->pos.z += _drive->velocity.z * base_get_dt() * 1000;
        /*
         *    Clip movement is not yet implemented.
         */
}

/*
 *    Tells clip movement if the player is on the ground.
 *
 *    @param unsigned char    1 if the player is on the ground, 0 otherwise.
 */
void drive_set_on_ground(unsigned char grounded) {
    _grounded = grounded;
}