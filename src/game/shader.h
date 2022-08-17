/*
 *    shader.c    --    source for the basic shader used by the engine
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 16, 2022.
 * 
 *    This file defines the functions for creating and manipulating shaders.
 *    At the moment, the only shader is the basic shader.
 */
#ifndef HOBKNIGHTS_SHADER_H
#define HOBKNIGHTS_SHADER_H

#include "libchik.h"

/*
 *    Sets up for a shader pass, this will be useful
 *    for performance.
 * 
 *    @param trap_t    The camera to use for projection.
 */
void shader_begin( trap_t sCamera );

/*
 *    This vertex layout contains the position, and texture coordinates.
 */
extern v_layout_t gVLayout;

#endif /* HOBKNIGHTS_SHADER_H  */