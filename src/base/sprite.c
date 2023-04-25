/*
 *    sprite.c    --    source for sprite operations
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on October 15, 2022.
 *
 *    This file is part of the Chik game base.
 *
 *    This file defines functions for creating and rendering sprites.
 */
#include "sprite.h"

#include <dirent.h>

#include "base.h"
#include "shaderops.h"

void *_quad = 0;

const vertex_t _verts[6] = {
    {{-1.0, -1.0, 1.0, 1.f}, {0.f, 0.f}},
    {{-1.0, 1.0, 1.0, 1.f}, {0.f, 1.f}},
    {{1.0, 1.0, 1.0, 1.f}, {1.f, 1.f}},
    {{-1.0, -1.0, 1.0, 1.f}, {0.f, 0.f}},
    {{1.0, -1.0, 1.0, 1.f}, {1.f, 0.f}},
    {{1.0, 1.0, 1.0, 1.f}, {1.f, 1.f}},
};

/*
 *    The sprite shader.
 *
 *    @param fragment_t *f        The raw fragment data.
 *    @param void       *v        The raw vertex data.
 *    @param void       *a        The assets.
 */
void basic_sprite_fshader(fragment_t *f, void *v, void *a) {
    vertex_t *vtx = (vertex_t *)v;

    image_t *img = *(image_t **)mesh_get_asset(a, 0);

    sample_texture(f, &vtx->tex, img);
}

void basic_sprite_vshader(void *v, void *v0, void *a) {
    vertex_t *vtx = (vertex_t *)v;

    vec2_t *pos   = (vec2_t *)mesh_get_asset(a, 1);
    vec2_t *scale = (vec2_t *)mesh_get_asset(a, 2);
    float  *rot   = (float *)mesh_get_asset(a, 3);

    vtx->pos.x = vtx->pos.x * scale->x;
    vtx->pos.y = vtx->pos.y * scale->y;

    vec2_t center = {vtx->pos.x, vtx->pos.y};

    vtx->pos.x = center.x * cos(*rot) - center.y * sin(*rot);
    vtx->pos.y = center.x * sin(*rot) + center.y * cos(*rot);

    vtx->pos.x += pos->x;
    vtx->pos.y += pos->y;
}

v_layout_t _sprite_layout = {
    .attributes =
        {/* Usage, Type, Stride, Offset, Fragment callback.  */
         {V_POS, V_R32G32B32A32_F, sizeof(vec4_t), 0},
         {0, V_R32G32_F, sizeof(vec2u_t), 16}},
    .count  = 2,
    .stride = sizeof(vertex_t),
    .f_fun  = &basic_sprite_fshader,
    .v_fun  = &basic_sprite_vshader,
};

/*
 *    Creates a sprite from a texture on disk.
 *
 *    @param const char *path    The path to the texture.
 *
 *    @return sprite_t     The sprite.
 */
sprite_t sprite_init(const char *path) {
    sprite_t sprite;

    if (_quad == (void *)0x0)
        _quad = vbuffer_create(_verts, sizeof(_verts), sizeof(_verts[0]), _sprite_layout);

    if (_quad == (void *)0x0) {
        LOGF_ERR("Failed to create sprite quad!\n");
        return sprite;
    }

    sprite.img   = image_create_from_file(path, 0);
    sprite.mesh  = mesh_create(_quad);
    sprite.pos   = (vec2_t){0.f, 0.f};
    sprite.scale = (vec2_t){1.f, 1.f};
    sprite.rot   = 0.f;

    mesh_append_asset(sprite.mesh, &sprite.img, sizeof(&sprite.img));
    mesh_append_asset(sprite.mesh, &sprite.pos, sizeof(&sprite.pos));
    mesh_append_asset(sprite.mesh, &sprite.scale, sizeof(&sprite.scale));
    mesh_append_asset(sprite.mesh, &sprite.rot, sizeof(&sprite.rot));

    return sprite;
}

/*
 *    Renders a sprite.
 *
 *    @param sprite_t *sprite    The sprite to render.
 */
void sprite_render(sprite_t *sprite) {
    mesh_set_asset(sprite->mesh, &sprite->pos, sizeof(sprite->pos), 1);
    mesh_set_asset(sprite->mesh, &sprite->scale, sizeof(sprite->scale), 2);
    mesh_set_asset(sprite->mesh, &sprite->rot, sizeof(sprite->rot), 3);

    mesh_draw(sprite->mesh);
}

/*
 *    Creates an avatar from a list of textures on disk.
 *
 *    @param const char *path    The path to the folder containing the textures.
 *
 *    @return avatar_t     The avatar.
 */
avatar_t avatar_init_dir(const char *path) {
    avatar_t       avatar;
    DIR           *dir;
    struct dirent *entry;
    unsigned int   i = 0;

    dir = opendir(path);
    if (dir == NULL) {
        return avatar;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG || strstr(entry->d_name, ".bmp")) {
            char pPath[256];
            realpath(".", pPath);
            sprintf(pPath, "%s/%s/%s", pPath, path, entry->d_name);

            avatar.sprites[i] = sprite_init(pPath);
            i++;
        }
    }

    avatar.count = i;

    return avatar;
}

/*
 *    Creates an avatar from an avatar file.
 *
 *    @param const char *path    The path to the avatar file.
 *
 *    @return avatar_t     The avatar.
 */
avatar_t avatar_init(const char *path) {}

/*
 *    Renders an avatar.
 *
 *    @param avatar_t *avatar    The avatar to render.
 */
void avatar_render(avatar_t *avatar) {
    unsigned long i;
    for (i = 0; i < avatar->count; i++)
        sprite_render(&avatar->sprites[i]);
}

/*
 *    Writes an avatar to disk.
 *
 *    @param avatar_t *    The avatar to write.
 *    @param const char *    The path to the avatar file.
 */
void avatar_write(avatar_t *spAvatar, const char *spPath) {}