/*
 *    shader.c    --    source for the basic shader used by the engine
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 16, 2022.
 *
 *    This file defines the functions for creating and manipulating shaders.
 *    At the moment, the only shader is the basic shader.
 */
#include "shader.h"

#include <math.h>

#include "../base/base.h"

#include "entity.h"

mat4_t     _projection                      = {0};
e_light_t *_light_idxs[MAX_ENTITIES]     = {nullptr};
vec3_t     _transformed_lights[MAX_ENTITIES] = {{0}};

bool _do_lighting = false;

vec3_t *_pos = nullptr;
vec3_t *_scale    = nullptr;
vec3_t *_rot = nullptr;

/*
 *    Performs bad lighting.
 *
 *    @param fragment_t *f    The fragment to draw to.
 *    @param vec4_t     *v    The vertex position.
 */
void bad_lighting(fragment_t *f, vec4_t *v) {
    vec4_t worldPos = {.x = v->x * v->w, .y = v->y * v->w, .z = 1 / v->z, .w = 1.f};

    /*
     *    Loop through all the lights and sum the color values.
     */
    vec3_t color = {0, 0, 0};
    size_t   i;
    for (i = 0; i < MAX_ENTITIES && _light_idxs[i] != nullptr; ++i) {
        /*
         *    Our distance will be squared, so we'll use the distance squared,
         *    saves us a sqrt.
         */
        float distance = pow(worldPos.x - _transformed_lights[i].x, 2.f) +
                         pow(worldPos.y - _transformed_lights[i].y, 2.f) +
                         pow(worldPos.z - _transformed_lights[i].z, 2.f);

        float attenuation = 1.f / distance;
        float intensity =
            _light_idxs[i]->intensity * (attenuation * attenuation);

        color.x += _light_idxs[i]->color.x * intensity;
        color.y += _light_idxs[i]->color.y * intensity;
        color.z += _light_idxs[i]->color.z * intensity;
    }

    /*
     *    Clamp the color values.
     */
    color.x = MAX(color.x, 0.f);
    color.x = MIN(color.x, 1.f);

    color.y = MAX(color.y, 0.f);
    color.y = MIN(color.y, 1.f);

    color.z = MAX(color.z, 0.f);
    color.z = MIN(color.z, 1.f);

    /*
     *    Now we'll calculate the diffuse color.
     */
    f->color.r *= color.x;
    f->color.g *= color.y;
    f->color.b *= color.z;
    f->color.a = 1;
}

/*
 *    The basic shader.
 *
 *    @param fragment_t *f        The raw fragment data.
 *    @param void       *v        The raw vertex data.
 *    @param void       *a        The uniform data.
 */
void basic_shader(fragment_t *f, void *v, void *a) {
    vertex_t *spVertex = (vertex_t *)v;
    image_t *img = *(image_t **)mesh_get_asset(a, 0);

    sample_texture(f, &spVertex->tex, img);

    if (_do_lighting == true)
        bad_lighting(f, &spVertex->pos);
}

/*
 *    Sets up for a shader pass, this will be useful
 *    for performance.
 *
 *    @param void *cam    The camera to use for projection.
 */
void shader_begin(void *cam) {
    _projection = get_camera_view(cam);

    size_t i;
    size_t j;
    for (i = 0, j = 0; i < MAX_ENTITIES; ++i) {
        e_light_t     *light = entity_get_light(i);
        e_transform_t *trans = entity_get_transform(i);
        if (light && trans) {
            /*
             *    Project the light sources.
             */
            mat4_t view = m4_mul_v4(
                _projection, (vec4_t){trans->pos.x, trans->pos.y,
                                      trans->pos.z, 1.f});

            _light_idxs[j]       = light;
            _transformed_lights[j++] = (vec3_t){view.v[0], view.v[4], view.v[8]};
        }
    }

    /*
     *    If these entities don't have lights, then we don't need to
     *    do anything, so we'll set the indices to -1 to indicate that.
     */
    for (; j < MAX_ENTITIES; ++j) {
        _light_idxs[j] = nullptr;
    }
}

/*
 *    Sets the shader lighting mode.
 *
 *    @param char *arg    Whether or not to do lighting.
 */
void shader_do_lighting(char *arg) {
    if (arg == nullptr)

        return;
    if (strncmp(arg, "true", 5) == 0)
        _do_lighting = true;
    else if (strncmp(arg, "false", 5) == 0)
        _do_lighting = false;
}

/*
 *    Sets the position of a mesh.
 *
 *    @param vec3_t *pos    The position of the mesh.
 */
void shader_set_position(vec3_t *pos) {
    _pos = pos;
}

/*
 *    Sets the scale of a mesh.
 *
 *    @param vec3_t *scale    The scale of the mesh.
 */
void shader_set_scale(vec3_t *scale) {
    _scale = scale;
}

/*
 *    Sets the rotation of a mesh.
 *
 *    @param vec3_t *rot    The rotation of the mesh.
 */
void shader_set_rotation(vec3_t *rot) {
    _rot = rot;
}

void basic_v_shader(void *v, void *v0, void *a) {
    vertex_t *vtx = (vertex_t *)v;
    mat4_t    m   = m4_identity();

    m.v[0] = vtx->pos.x;
    m.v[4] = vtx->pos.y;
    m.v[8] = vtx->pos.z;

    if (_scale != nullptr) {
        vtx->pos.x *= _scale->x;
        vtx->pos.y *= _scale->y;
        vtx->pos.z *= _scale->z;
    }

    if (_rot != nullptr) {
        m = m4_mul_v4(m4_rotate(_rot->x, (vec3_t){1.f, 0.f, 0.f}), vtx->pos);
        m = m4_mul_m4(m4_rotate(_rot->y, (vec3_t){0.f, 1.f, 0.f}), m);
        m = m4_mul_m4(m4_rotate(_rot->z, (vec3_t){0.f, 0.f, 1.f}), m);
    }

    if (_pos != nullptr) {
        m.v[0] += _pos->x;
        m.v[4] += _pos->y;
        m.v[8] += _pos->z;
    }

    m = m4_mul_m4(_projection, m);

    vtx->pos.x = m.v[0];
    vtx->pos.y = m.v[4];
    vtx->pos.z = m.v[8];
    vtx->pos.w = m.v[12];
}

void vtx_scale(void *vd, void *v0, float t) {
    vertex_t *vdv = (vertex_t *)vd;
    vertex_t *v0v = (vertex_t *)v0;

    memcpy(&vdv->pos, &v0v->pos, sizeof(vec4_t));

    vdv->tex.x = v0v->tex.x * t;
    vdv->tex.y = v0v->tex.y * t;
}

void vtx_add(void *vd, void *v0, void *v1) {
    vertex_t *vdv = (vertex_t *)vd;
    vertex_t *v0v = (vertex_t *)v0;
    vertex_t *v1v = (vertex_t *)v1;

    vdv->pos.x = v0v->pos.x + v1v->pos.x;
    vdv->pos.y = v0v->pos.y + v1v->pos.y;
    vdv->pos.z = v0v->pos.z + v1v->pos.z;
    vdv->pos.w = v0v->pos.w + v1v->pos.w;

    vdv->tex.x = v0v->tex.x + v1v->tex.x;
    vdv->tex.y = v0v->tex.y + v1v->tex.y;
}

v_layout_t _v_layout = {
    .attributes =
        {/* Usage, Type, Stride, Offset, Fragment callback.  */
         {V_POS, V_R32G32B32A32_F, sizeof(vec4_t), 0},
         {0, V_R32G32_F, sizeof(vec2u_t), 16}},
    .count   = 2,
    .stride  = sizeof(vertex_t),
    .v_scale = &vtx_scale,
    .v_add   = &vtx_add,
    .v_fun   = &basic_v_shader,
    .f_fun   = &basic_shader,
};