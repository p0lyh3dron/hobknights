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
#include "shader.h"

#include "../game/entity.h"

/*
 *    The basic shader.
 *
 *    @param fragment_t *        The raw fragment data.
 *    @param void       *        The raw vertex data.
 *    @param void       *        The uniform data.
 *    @param void       *        The raw unprocessed vertex data.
 */
void basic_shader( fragment_t *spF, void *spV, void *spU ) {
    chik_vertex_t *spVertex = ( chik_vertex_t * )spV;
    sample_texture( spF, &spVertex->aTexCoord, spU );
    bad_lighting( spF, &spVertex->aPos );
}

/*
 *    Samples a texture at the given UV coordinates.
 *
 *    @param fragment_t *    The fragment to draw to.
 *    @param vec2_t     *    The UV coordinates to sample.
 *    @param void       *    The texture to sample.
 */
void sample_texture( fragment_t *spFrag, vec2_t *spUV, void *spData ) {
    texture_t *pTex = ( texture_t* )spData;
    image_t   *pImage = pTex->apImage;

    if ( !spData || !pTex || !pImage ) {
        return;
    }

    vec2u_t sUV = {
        .x = ( u32 )( fmod( spUV->x, 1.0f ) * pImage->aWidth ),
        .y = ( u32 )( fmod( spUV->y, 1.0f ) * pImage->aHeight)
    };

    spFrag->aColor.r = ( ( u8* )pImage->apData )[ ( sUV.x + sUV.y * pImage->aWidth ) * 3 + 0 ];
    spFrag->aColor.g = ( ( u8* )pImage->apData )[ ( sUV.x + sUV.y * pImage->aWidth ) * 3 + 1 ];
    spFrag->aColor.b = ( ( u8* )pImage->apData )[ ( sUV.x + sUV.y * pImage->aWidth ) * 3 + 2 ];
    spFrag->aColor.a = 1;
}

vec4_t gLight    = { 0.f, 0.f, 0.f, 1.f };
vec3_t gLightHue = { 30.f / 255, 11.f / 255, 176.f / 255.f };

/*
 *    Performs bad lighting.
 *
 *    @param fragment_t *    The fragment to draw to.
 *    @param vec4_t     *    The vertex position.
 */
void bad_lighting( fragment_t *spFrag, vec4_t *spV ) {
    vec4_t worldPos = {
        .x = spV->x * spV->w,
        .y = spV->y * spV->w,
        .z = 1 / spV->z,
        .w = 1.f
    };

    f32 distance = sqrt( pow( worldPos.x - gLight.x, 2.f ) + pow( worldPos.y - gLight.y, 2 ) + pow( worldPos.z - gLight.z, 2 ) );
    f32 attenuation = 1.f / ( distance * distance );
    f32 intensity = 90 * ( attenuation * attenuation );
    intensity = MAX( intensity, 0.f );
    intensity = MIN( intensity, 1.f );
    spFrag->aColor.r *= intensity * gLightHue.x;
    spFrag->aColor.g *= intensity * gLightHue.y;
    spFrag->aColor.b *= intensity * gLightHue.z;
    spFrag->aColor.a = 1;
}

v_layout_t gVLayout = {
    .aAttribs = { 
        /* Usage, Type, Stride, Offset, Fragment callback.  */
        { V_POS, V_R32G32B32A32_F,     sizeof( vec4_t ),  0  },
        { 0,     V_R32G32_F,           sizeof( vec2u_t ), 16 }
    },
    .aCount   = 2,
    .aStride  = sizeof( chik_vertex_t ),
    .apFunc   = &basic_shader,
};