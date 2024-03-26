/*
 *    text.c    --    source for abstracting text rendering
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on August 13, 2022
 *
 *    This file is part of the Chik game base.
 *
 *    This file defines functions for rendering text.
 */
#include "text.h"

#include <string.h>

#include "base.h"

text_t *_cur_text;

/*
 *    The text fragment shader.
 *
 *    @param fragment_t *f            The raw fragment data.
 *    @param void       *v            The raw vertex data.
 *    @param void       *asset        The uniform data.
 */
void text_shader(fragment_t *f, void *v, void *asset) {
    vertex_t *vtx = (vertex_t *)v;

    image_t *img = *(image_t **)mesh_get_asset(asset, 0);

    sample_texture(f, &vtx->tex, img);
}

/*
 *    The text vertex layout.
 *
 *    @param void *v     The output vertex data.
 *    @param void *v0     The raw vertex data.
 *    @param void *u     The uniform data.
 */
void text_vertex(void *v, void *v0, void *u) {
    vertex_t *vtx = (vertex_t *)v;
    vtx->pos.x *= _cur_text->scale.x * _cur_text->aspect;
    vtx->pos.y *= _cur_text->scale.y;

    vtx->pos.x += _cur_text->pos.x;
    ;
    vtx->pos.y += _cur_text->pos.y;
}

v_layout_t _text_layout = {
    .attributes =
        {/* Usage, Type, Stride, Offset, Fragment callback.  */
         {V_POS, V_R32G32B32A32_F, sizeof(vec4_t), 0},
         {0, V_R32G32_F, sizeof(vec2u_t), 16}},
    .count  = 2,
    .stride = sizeof(vertex_t),
    .v_fun  = &text_vertex,
    .f_fun  = &text_shader,
};

/*
 *    Creates a mesh for rendering text.
 *
 *    @param const char *text     The text to render.
 *    @param vec2_t align       The text alignment.
 *
 *    @return text_t *      The text mesh.
 */
text_t *text_init(const char *text, vec2_t align) {
    vertex_t verts[6] = {
        {{-1.f + align.x, -1.f + align.y, 1.f, 1.f}, {0.f, 0.f}},
        {{-1.f + align.x, 1.f + align.y, 1.f, 1.f}, {0.f, 1.f}},
        {{1.f + align.x, 1.f + align.y, 1.f, 1.f}, {1.f, 1.f}},
        {{-1.f + align.x, -1.f + align.y, 1.f, 1.f}, {0.f, 0.f}},
        {{1.f + align.x, -1.f + align.y, 1.f, 1.f}, {1.f, 0.f}},
        {{1.f + align.x, 1.f + align.y, 1.f, 1.f}, {1.f, 1.f}},
    };

    void *v =
        vbuffer_create(&verts, sizeof(verts), sizeof(vertex_t), _text_layout);
    image_t *t = text_create(text);

    void *m = mesh_create(v);

    mesh_append_asset(m, (void *)&t, sizeof(image_t *));

    vec2_t res = get_screen_size();

    text_t *txt = (text_t *)malloc(sizeof(text_t));

    if (txt == (text_t *)0x0) {
        return (text_t *)0x0;
    }

    txt->mesh  = m;
    txt->img   = t;
    txt->pos   = (vec2_t){0.f, 0.f};
    txt->scale = (vec2_t){1.f, 1.f};
    /*
     *    The internal font is a monospace 8x13 font.
     */
    txt->aspect = 8.f * strlen(text) * res.y / 13.f / res.x;

    return txt;
}

/*
 *    Updates the text texture.
 *
 *    @param text_t *text          The text mesh.
 *    @param const char *new_text    The text to render.
 */
void text_update(text_t *text, const char *new_text) {
    //texture_free(text->img);
    //
    //image_t *i = text_create(new_text);
    //
    //if (i == (image_t *)0x0) {
    //    LOGF_ERR("Failed to create text image.");
    //    return;
    //}
    //
    //mesh_append_asset(text->mesh, i, sizeof(image_t));
    //text->img = i;
}

/*
 *    Sets the position of the text.
 *
 *    @param text_t *text      The handle to the text.
 *    @param vec2_t pos        The position of the text.
 */
void text_set_position(text_t *text, vec2_t pos) {
    if (text == (text_t *)0x0) {
        LOGF_ERR("Null pointer passed to text_set_position.");
        return;
    }

    text->pos = pos;
}

/*
 *    Sets the scale of the text.
 *
 *    @param text_t *text       The handle to the text.
 *    @param vec2_t  scale      The scale of the text.
 */
void text_set_scale(text_t *text, vec2_t scale) {
    if (text == (text_t *)0x0) {
        LOGF_ERR("Null pointer passed to text_set_scale.");
        return;
    }

    text->scale = scale;
}

/*
 *    Renders the text.
 *
 *    @param text_t *text      The text to render.
 */
void text_render(text_t *text) {
    if (text == (text_t *)0x0) {
        LOGF_ERR("Null pointer passed to text_render.");
        return;
    }

    _cur_text = text;

    mesh_draw(text->mesh);
}