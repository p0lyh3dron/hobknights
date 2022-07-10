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

#include "entity.h"

mat4_t         gProjection                          = { 0         };
e_light_t     *gpLightIndices[ MAX_ENTITIES ]       = { nullptr   };
vec3_t         gTransformedLights[ MAX_ENTITIES ]   = { { 0 }     };

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

    /*
     *    Loop through all the lights and sum the color values.
     */
    vec3_t color = { 0, 0, 0 };
    s64 i;
    for ( i = 0; i < MAX_ENTITIES && gpLightIndices[ i ] != nullptr; ++i ) {
        /*
         *    Our distance will be squared, so we'll use the distance squared,
         *    saves us a sqrt.
         */
        f32 distance    = pow( worldPos.x - gTransformedLights[ i ].x, 2.f ) + 
                          pow( worldPos.y - gTransformedLights[ i ].y, 2.f ) + 
                          pow( worldPos.z - gTransformedLights[ i ].z, 2.f );

        f32 attenuation = 1.f / distance;
        f32 intensity   = gpLightIndices[ i ]->aIntensity * ( attenuation * attenuation );

        color.x += gpLightIndices[ i ]->aColor.x * intensity;
        color.y += gpLightIndices[ i ]->aColor.y * intensity;
        color.z += gpLightIndices[ i ]->aColor.z * intensity;
    }

    /*
     *    Clamp the color values.
     */
    color.x = MAX( color.x, 0.f );
    color.x = MIN( color.x, 1.f );

    color.y = MAX( color.y, 0.f );
    color.y = MIN( color.y, 1.f );

    color.z = MAX( color.z, 0.f );
    color.z = MIN( color.z, 1.f );

    /*
     *    Now we'll calculate the diffuse color.
     */
    spFrag->aColor.r *= color.x;
    spFrag->aColor.g *= color.y;
    spFrag->aColor.b *= color.z;
    spFrag->aColor.a = 1;
}

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

/*
 *    Sets up for a shader pass, this will be useful
 *    for performance.
 * 
 *    @param handle_t    The camera to use for projection.
 */
void shader_begin( handle_t sCamera ) {
    gProjection = get_camera_view( sCamera );

    s64 i;
    s64 j;
    for ( i = 0, j = 0; i < MAX_ENTITIES; ++i ) {
        e_light_t     *pLight = entity_get_light( i );
        e_transform_t *pTrans = entity_get_transform( i );
        if ( pLight && pTrans ) {
            /*
             *    Project the light sources.
             */
            mat4_t view = m4_mul_v4( gProjection, ( vec4_t ){ pTrans->aPosition.x, pTrans->aPosition.y, pTrans->aPosition.z, 1.f } );

            gpLightIndices[ j ]        = pLight;
            gTransformedLights[ j++ ]  = ( vec3_t ){ view.v[ 0 ], view.v[ 4 ], view.v[ 8 ] };
        }
    }
    /*
     *    If these entities don't have lights, then we don't need to
     *    do anything, so we'll set the indices to -1 to indicate that.
     */
    for ( ; j < MAX_ENTITIES; ++j ) {
        gpLightIndices[ j ]     = nullptr;
    }
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