/*
 *    text.h    --    header for abstracting text rendering
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on August 13, 2022
 *
 *    This file is part of the Chik game base.
 *
 *    This file defines types for rendering.
 */
#ifndef BASE_TYPES_H
#define BASE_TYPES_H

#include "libchik.h"

typedef struct {
    vec4_t pos;
    vec2_t tex;
} vertex_t;

#endif /* BASE_TYPES_H  */