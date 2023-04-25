#pragma once

#include "libchik.h"

typedef struct {
    int    id;
    vec3_t pos;
    vec2_t rot;
    vec3_t scale;
} e_transform_t;

typedef enum {
    DRIVE_NOCLIP,
    DRIVE_CLIP,
} e_drivable_movetype_e;

typedef struct {
    int                   id;
    float                 speed;
    e_drivable_movetype_e move_type;
} e_driveable_t;

typedef struct {
    int    id;
    vec3_t origin_offset;
} e_camera_t;

typedef struct {
    int    id;
    float  intensity;
    vec3_t color;
} e_light_t;

typedef struct {
    int      id;
    model_t *model;
} e_model_t;