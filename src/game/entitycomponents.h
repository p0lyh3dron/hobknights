#pragma once

#include "libchik.h"

typedef struct {
    s32    aId;
    vec3_t aPosition;
    vec2_t aRotation;
    vec3_t aScale;
} e_transform_t;

typedef enum {
    DRIVE_NOCLIP,
    DRIVE_CLIP,
} e_drivable_movetype_e;

typedef struct {
    s32                   aId;
    f32                   aSpeed;
    e_drivable_movetype_e aMoveType;
} e_driveable_t;

typedef struct {
    s32    aId;
    vec3_t aOriginOffset;
} e_camera_t;

typedef struct {
    s32    aId;
    f32    aIntensity;
    vec3_t aColor;
} e_light_t;

typedef struct {
    s32     aId;
    model_t aModel;
} e_model_t;