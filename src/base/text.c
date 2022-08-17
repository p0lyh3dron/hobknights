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

/*
 *    The text shader.
 *
 *    @param fragment_t *        The raw fragment data.
 *    @param void       *        The raw vertex data.
 *    @param void       *        The uniform data.
 *    @param void       *        The raw unprocessed vertex data.
 */
void text_shader( fragment_t *spF, void *spV, void *spU ) {
    chik_vertex_t *pV = ( chik_vertex_t* )spV;

    sample_texture( spF, &pV->aTexCoord, spU );
}

v_layout_t gTextLayout = {
    .aAttribs = { 
        /* Usage, Type, Stride, Offset, Fragment callback.  */
        { V_POS, V_R32G32B32A32_F,     sizeof( vec4_t ),  0  },
        { 0,     V_R32G32_F,           sizeof( vec2u_t ), 16 }
    },
    .aCount   = 2,
    .aStride  = sizeof( chik_vertex_t ),
    .apFunc   = &text_shader,
};

/*
 *    Creates a mesh for rendering text.
 *
 *    @param const s8 *    The text to render.
 *    @param vec2_t        The text alignment.
 *    
 *    @return text_t       The text mesh.
 */
text_t text_init( const s8 *spText, vec2_t sAlignment ) {
    chik_vertex_t verts[ 6 ] = {
        { { -1.f + sAlignment.x, -1.f + sAlignment.y, 1.f, 1.f }, { 0.f, 0.f } },
        { { -1.f + sAlignment.x,  1.f + sAlignment.y, 1.f, 1.f }, { 0.f, 1.f } },
        { {  1.f + sAlignment.x,  1.f + sAlignment.y, 1.f, 1.f }, { 1.f, 1.f } },
        { { -1.f + sAlignment.x, -1.f + sAlignment.y, 1.f, 1.f }, { 0.f, 0.f } },
        { {  1.f + sAlignment.x, -1.f + sAlignment.y, 1.f, 1.f }, { 1.f, 0.f } },
        { {  1.f + sAlignment.x,  1.f + sAlignment.y, 1.f, 1.f }, { 1.f, 1.f } },
    };

    trap_t v = vbuffer_create( &verts, sizeof( verts ), sizeof( chik_vertex_t ), gTextLayout );
    trap_t t = text_create( spText );

    trap_t m = mesh_create( v, t );

    mesh_set_skip_projection( m );
    mesh_set_skip_clipping( m );

    vec2_t res = get_screen_size();

    text_t text = {
        .aMesh     = m,
        .aTexture  = t,
        .aPosition = { 0.f, 0.f },
        .aScale    = { 1.f, 1.f },
        /*
         *    The internal font is a monospace 8x13 font.
         */
        .aAspect   = 8.f * strlen( spText ) * res.y / 13.f / res.x,
    };

    return text;
}

/*
 *    Updates the text texture.
 *
 *    @param text_t *      The text mesh.
 *    @param const s8 *    The text to render.
 */
void text_update( text_t *pText, const s8 *spText ) {
    texture_free( pText->aTexture );
    
    trap_t t = text_create( spText );
    mesh_set_texture( pText->aMesh, t );
    pText->aTexture = t;
}

/*
 *    Sets the position of the text.
 *
 *    @param text_t *      The handle to the text.
 *    @param vec2_t        The position of the text.
 */
void text_set_position( text_t *spText, vec2_t sPosition ) {
    if ( spText == nullptr ) {
        return;
    }
    spText->aPosition = sPosition;
}

/*
 *    Sets the scale of the text.
 *
 *    @param text_t *      The handle to the text.
 *    @param vec2_t        The scale of the text.
 */
void text_set_scale( text_t *spText, vec2_t sScale ) {
    if ( spText == nullptr ) {
        return;
    }
    spText->aScale = sScale;
}

/*
 *    Renders the text.
 *
 *    @param text_t      The text to render.
 */
void text_render( text_t sText ) {
    if ( BAD_TRAP( sText.aMesh ) ) {
        return;
    }
    mesh_translate( ( vec3_t ){ sText.aPosition.x, sText.aPosition.y, 0.f } );
    mesh_rotate( ( vec3_t ){ 0.f, 0.f, 0.f } );
    mesh_scale( ( vec3_t ){ sText.aScale.x * sText.aAspect, sText.aScale.y, 1.f } );
    mesh_draw( sText.aMesh );
}