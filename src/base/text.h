/*
 *    text.h    --    header for abstracting text rendering
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on August 13, 2022
 *
 *    This file is part of the Chik game base.
 * 
 *    This file declares functions for rendering text.
 */
#ifndef BASE_TEXT_H
#define BASE_TEXT_H

#include "libchik.h"

#define BASE_TEXT_ALIGN_TOPRIGHT     ( vec2_t ){ -1.f, -1.f }
#define BASE_TEXT_ALIGN_TOPCENTER    ( vec2_t ){  0.f, -1.f }
#define BASE_TEXT_ALIGN_TOPLEFT      ( vec2_t ){  1.f, -1.f }
#define BASE_TEXT_ALIGN_CENTERRIGHT  ( vec2_t ){ -1.f,  0.f }
#define BASE_TEXT_ALIGN_CENTER       ( vec2_t ){  0.f,  0.f }
#define BASE_TEXT_ALIGN_CENTERLEFT   ( vec2_t ){  1.f,  0.f }
#define BASE_TEXT_ALIGN_BOTTOMRIGHT  ( vec2_t ){ -1.f,  1.f }
#define BASE_TEXT_ALIGN_BOTTOMCENTER ( vec2_t ){  0.f,  1.f }
#define BASE_TEXT_ALIGN_BOTTOMLEFT   ( vec2_t ){  1.f,  1.f }

typedef struct {
    trap_t aMesh;
    trap_t aTexture;
    vec2_t   aPosition;
    vec2_t   aScale;
    f32      aAspect;
} text_t;

/*
 *    Creates a mesh for rendering text.
 *
 *    @param const s8 *    The text to render.
 *    @param vec2_t        The text alignment.
 *    
 *    @return text_t       The text mesh.
 */
text_t text_init( const s8 *spText, vec2_t sAlignment );

/*
 *    Updates the text texture.
 *
 *    @param text_t *      The text mesh.
 *    @param const s8 *    The text to render.
 */
void text_update( text_t *pText, const s8 *spText );

/*
 *    Sets the position of the text.
 *
 *    @param text_t *      The handle to the text.
 *    @param vec2_t        The position of the text.
 */
void text_set_position( text_t *spText, vec2_t sPosition );

/*
 *    Sets the scale of the text.
 *
 *    @param text_t *      The handle to the text.
 *    @param vec2_t        The scale of the text.
 */
void text_set_scale( text_t *spText, vec2_t sScale );

/*
 *    Renders the text.
 *
 *    @param text_t      The text to render.
 */
void text_render( text_t sText );

#endif /* BASE_TEXT_H  */