/*
 *    shaderops.h    --    header for general shader operations
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on August 13, 2022.
 *
 *    This file is part of the Chik game base.
 *
 *    Made out of convenience to not copy and paste code.
 */
#ifndef CHIK_SHADEROPS_H
#define CHIK_SHADEROPS_H

#include "libchik.h"

/*
 *    Samples a texture at the given UV coordinates.
 *
 *    @param fragment_t *f        The fragment to draw to.
 *    @param vec2_t     *uv       The UV coordinates to sample.
 *    @param image_t    *asset    The texture to sample.
 */
color32_t sample_texture(fragment_t *f, vec2_t *uv, image_t *img);

#endif /* CHIK_SHADEROPS_H  */