/*
 *    sprite.h    --    header for sprite operations
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on October 15, 2022.
 *
 *    This file is part of the Chik game base.
 *
 *    This file declares functions for creating and rendering sprites.
 */
#ifndef BASE_SPRITE_H
#define BASE_SPRITE_H

#include "libchik.h"

typedef struct {
    void  *mesh;
    void  *img;
    vec2_t pos;
    vec2_t scale;
    float  rot;
    float  aspect;
} sprite_t;

typedef struct {
    sprite_t     sprites[64];
    unsigned int count;
} avatar_t;

/*
 *    Creates a sprite from a texture on disk.
 *
 *    @param const char *    The path to the texture.
 *
 *    @return sprite_t     The sprite.
 */
sprite_t sprite_init(const char *spPath);

/*
 *    Renders a sprite.
 *
 *    @param sprite_t *    The sprite to render.
 */
void sprite_render(sprite_t *spSprite);

/*
 *    Creates an avatar from a list of textures on disk.
 *
 *    @param const char *    The path to the folder containing the textures.
 *
 *    @return avatar_t     The avatar.
 */
avatar_t avatar_init_dir(const char *spPath);

/*
 *    Creates an avatar from an avatar file.
 *
 *    @param const char *    The path to the avatar file.
 *
 *    @return avatar_t     The avatar.
 */
avatar_t avatar_init(const char *spPath);

/*
 *    Renders an avatar.
 *
 *    @param avatar_t *    The avatar to render.
 */
void avatar_render(avatar_t *spAvatar);

/*
 *    Writes an avatar to disk.
 *
 *    @param avatar_t *    The avatar to write.
 *    @param const char *    The path to the avatar file.
 */
void avatar_write(avatar_t *spAvatar, const char *spPath);

#endif /* BASE_SPRITE_H  */