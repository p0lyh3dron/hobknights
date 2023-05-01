/*
 *    collision.c    --    source for collisions
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on April 27, 2023.
 *
 *    This file is part of the Chik game base.
 *
 *    This file defines the algebraic functions for collisions.
 */
#include "collision.h"

#define COLLISION_EPSILON 1.f
#define CYLINDER_EDGES 16
#define CYLINDER_DIVISIONS 16

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
vec3_t collision_cylinder_plane(vec3_t v_c, float r_c, float h_c, vec3_t v_0, vec3_t v_1, vec3_t v_2) {
    vec3_t  collision = {0, 0, 0};
    plane_t p;

    plane_from_points(&p, &v_0, &v_1, &v_2);

    unsigned long i;
    for (i = 0; i < CYLINDER_EDGES; ++i) {
        vec2_t dsn;
        /* Shoot rays out from top and bottom of cylinder.  */
        vec3_t v = {r_c * cosf((float)i / CYLINDER_EDGES * 2 * PI), 0, r_c * sinf((float)i / CYLINDER_EDGES * 2 * PI)};

        float plane_dot = vec3_dot(&v, &p.normal);

        /* Parallel.  */
        if (fabs(plane_dot) < 0.1f)
            continue;

        float d = -vec3_dot(&v_0, &p.normal);

        float t = -(vec3_dot(&v_c, &p.normal) + d) / plane_dot;

        vec3_t v_tdir;
        vec3_t v_p;

        vec3_scale(&v_tdir, &p.normal, t);
        vec3_add(&v_p, &v_c, &v_tdir);

        vec3_t edge;
        vec3_t pln;
        vec3_t n;
        vec3_sub(&edge, &v_1, &v_0);
        vec3_sub(&pln, &v_p, &v_0);

        vec3_cross(&n, &edge, &pln);

        if (vec3_dot(&p.normal, &n) < 0.f)
            continue;

        vec3_sub(&edge, &v_2, &v_1);
        vec3_sub(&pln, &v_p, &v_1);

        vec3_cross(&n, &edge, &pln);

        if (vec3_dot(&p.normal, &n) < 0.f)
            continue;

        vec3_sub(&edge, &v_0, &v_2);
        vec3_sub(&pln, &v_p, &v_2);

        vec3_cross(&n, &edge, &pln);

        if (vec3_dot(&p.normal, &n) < 0.f)
            continue;

        if (fabs(t) < 1) {
            collision.x += v.x * (1 - t);
            collision.y += v.y * (1 - t);
            collision.z += v.z * (1 - t);

            v_c.x += collision.x;
            v_c.y += collision.y;
            v_c.z += collision.z;
        }
    }

    for (i = 0; i < CYLINDER_DIVISIONS; ++i) {
        vec2_t dsn;
        /* Shoot rays out from top and bottom of cylinder.  */
        vec3_t v = {0, h_c/2, 0};
        vec3_t v_r = v_c;

        v_r.x += r_c * cosf((float)i / CYLINDER_DIVISIONS * 2 * PI);
        v_r.z += r_c * sinf((float)i / CYLINDER_DIVISIONS * 2 * PI);

        float plane_dot = vec3_dot(&v, &p.normal);

        /* Parallel.  */
        if (fabs(plane_dot) < 0.1f)
            continue;

        float d = -vec3_dot(&v_0, &p.normal);

        float t = -(vec3_dot(&v_r, &p.normal) + d) / plane_dot;

        vec3_t v_tdir;
        vec3_t v_p;

        vec3_scale(&v_tdir, &p.normal, t);
        vec3_add(&v_p, &v_r, &v_tdir);

        vec3_t edge;
        vec3_t pln;
        vec3_t n;
        vec3_sub(&edge, &v_1, &v_0);
        vec3_sub(&pln, &v_p, &v_0);

        vec3_cross(&n, &edge, &pln);

        if (vec3_dot(&p.normal, &n) < 0.f)
            continue;

        vec3_sub(&edge, &v_2, &v_1);
        vec3_sub(&pln, &v_p, &v_1);

        vec3_cross(&n, &edge, &pln);

        if (vec3_dot(&p.normal, &n) < 0.f)
            continue;

        vec3_sub(&edge, &v_0, &v_2);
        vec3_sub(&pln, &v_p, &v_2);

        vec3_cross(&n, &edge, &pln);

        if (vec3_dot(&p.normal, &n) < 0.f)
            continue;

        if (fabs(t) < 1) {
            collision.x += v.x * (1 - fabs(t)) * (t < 0 ? 1 : -1);
            collision.y += v.y * (1 - fabs(t)) * (t < 0 ? 1 : -1);
            collision.z += v.z * (1 - fabs(t)) * (t < 0 ? 1 : -1);

            v_c.x += collision.x;
            v_c.y += collision.y;
            v_c.z += collision.z;
        }
    }

    return collision;
}

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
vec3_t collision_cylinder_model(vec3_t v_c, float r_c, float h_c, model_t *m) {
    vec3_t collision = {0, 0, 0};

    unsigned long i;
    for (i = 0; i < m->num_collision_verts; i += 3) {
        vec3_t v_0 = m->collision_mesh[i + 0];
        vec3_t v_1 = m->collision_mesh[i + 1];
        vec3_t v_2 = m->collision_mesh[i + 2];

        vec3_t n = collision_cylinder_plane(v_c, r_c, h_c, v_0, v_1, v_2);

        collision.x += n.x;
        collision.y += n.y;
        collision.z += n.z;

        v_c.x += collision.x;
        v_c.y += collision.y;
        v_c.z += collision.z;
    }

    return collision;
}