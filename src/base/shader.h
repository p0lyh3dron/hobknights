/*
 *    shader.c    --    source for the basic shader used by the engine
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 16, 2022.
 * 
 *    This file is part of the Chik game base.
 * 
 *    This file defines the functions for creating and manipulating shaders.
 *    At the moment, the only shader is the basic shader.
 */
#ifndef BASE_SHADER_H
#define BASE_SHADER_H

#include "libchik.h"

/*
 *    Samples a texture at the given UV coordinates.
 *
 *    @param fragment_t *    The fragment to draw to.
 *    @param vec2_t     *    The UV coordinates to sample.
 *    @param void       *    The texture to sample.
 */
void sample_texture( fragment_t *spFrag, vec2_t *spUV, void *spData );

extern v_layout_t gVLayout;

#endif /* BASE_SHADER_H  */