#pragma once

#include "libchik.h"

typedef struct {
    u32    aId;
    vec3_t aPosition;
    vec2_t aRotation;
} e_transform_t;

typedef enum {
    DRIVE_NOCLIP,
    DRIVE_CLIP,
} e_drivable_movetype_e;

typedef struct {
    u32                   aId;
    e_drivable_movetype_e aMoveType;
} e_driveable_t;

typedef struct {
    u32    aId;
    vec3_t aOriginOffset;
} e_camera_t;