/*
 *    shaderops.c    --    source for general shader operations
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on August 13, 2022.
 *
 *    This file is part of the Chik game base.
 *
 *    Made out of convenience to not copy and paste code.
 */
#include "shaderops.h"

/*
 *    Samples a texture at the given UV coordinates.
 *
 *    @param fragment_t *f        The fragment to draw to.
 *    @param vec2_t     *uv       The UV coordinates to sample.
 *    @param image_t    *asset    The texture to sample.
 */
void sample_texture(fragment_t *f, vec2_t *uv, image_t *img) {
    vec2u_t int_uv = {.x = (unsigned int)(uv->x * img->width) % img->width,
                      .y = (unsigned int)(uv->y * img->height) % img->height};
    
    unsigned int pixel;

    memcpy(&pixel, (unsigned char *)img->buf + (int_uv.x + int_uv.y * img->width) * 4, 4);

    f->color.r = pixel & 0xFF;
    f->color.g = pixel >> 8 & 0xFF;
    f->color.b = pixel >> 16 & 0xFF;
    f->color.a = pixel >> 24 & 0xFF;
}