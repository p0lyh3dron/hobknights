/*
 *    collision.h    --    header for collisions
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on April 27, 2023.
 *
 *    This file is part of the Chik game base.
 *
 *    This file gives functions for collision detection and response.
 */
#ifndef BASE_COLLISION_H
#define BASE_COLLISION_H

#include "libchik.h"

#include "model.h"

/*
 *    Checks a collision between a cylinder and a plane.
 *    Returns a vector representing the collision normal.
 *    If there is no collision, returns a zero vector.
 * 
 *    @param vec3_t v_c    The center of the cylinder.
 *    @param float  r_c    The radius of the cylinder.
 *    @param float  h_c    The height of the cylinder.
 *    @param vec3_t v_0    The first vertex of the plane.
 *    @param vec3_t v_1    The second vertex of the plane.
 *    @param vec3_t v_2    The third vertex of the plane.
 * 
 *    @return vec3_t       The collision normal.
 */
vec3_t collision_cylinder_plane(vec3_t v_c, float r_c, float h_c, vec3_t v_0, vec3_t v_1, vec3_t v_2);

/*
 *    Checks a collision between a cylinder and a model.
 *
 *    @param vec3_t   v_c    The center of the cylinder.
 *    @param float    r_c    The radius of the cylinder.
 *    @param float    h_c    The height of the cylinder.
 *    @param model_t *m      The model to check.
 * 
 *    @return vec3_t         The collision normal.
 */
vec3_t collision_cylinder_model(vec3_t v_c, float r_c, float h_c, model_t *m);

#endif /* BASE_COLLISION_H  */