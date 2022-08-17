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
 *    @param fragment_t *    The fragment to draw to.
 *    @param vec2_t     *    The UV coordinates to sample.
 *    @param void       *    The texture to sample.
 */
void sample_texture( fragment_t *spFrag, vec2_t *spUV, void *spData ) {
    texture_t *pTex   = ( texture_t* )spData;
    image_t   *pImage = pTex->apImage;

    if ( !spData || !pTex || !pImage ) {
        return;
    }

    vec2u_t sUV = {
        .x = ( u32 )( fmod( spUV->x, 1.0f ) * pImage->aWidth ),
        .y = ( u32 )( fmod( spUV->y, 1.0f ) * pImage->aHeight)
    };

    spFrag->aColor.r = ( ( u8* )pImage->apData )[ ( sUV.x + sUV.y * pImage->aWidth ) * 4 + 0 ];
    spFrag->aColor.g = ( ( u8* )pImage->apData )[ ( sUV.x + sUV.y * pImage->aWidth ) * 4 + 1 ];
    spFrag->aColor.b = ( ( u8* )pImage->apData )[ ( sUV.x + sUV.y * pImage->aWidth ) * 4 + 2 ];
    spFrag->aColor.a = ( ( u8* )pImage->apData )[ ( sUV.x + sUV.y * pImage->aWidth ) * 4 + 3 ];
}