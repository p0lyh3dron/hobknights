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
 *    @param void *cam    The camera to use for projection.
 */
void shader_begin(void *cam);

/*
 *    Sets the shader lighting mode.
 *
 *    @param char *arg    Whether or not to do lighting.
 */
void shader_do_lighting(char *arg);

/*
 *    Sets the position of a mesh.
 *
 *    @param vec3_t *pos    The position of the mesh.
 */
void shader_set_position(vec3_t *pos);

/*
 *    Sets the scale of a mesh.
 *
 *    @param vec3_t *scale    The scale of the mesh.
 */
void shader_set_scale(vec3_t *scale);

/*
 *    Sets the rotation of a mesh.
 *
 *    @param vec3_t *rot   The rotation of the mesh.
 */
void shader_set_rotation(vec3_t *rot);

/*
 *    This vertex layout contains the position, and texture coordinates.
 */
extern v_layout_t _v_layout;

#endif /* HOBKNIGHTS_SHADER_H  */