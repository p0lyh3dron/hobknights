/*
 *    model.h    --    header for models
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 7th, 2022.
 * 
 *    This file is part of the Chik game base.
 * 
 *    This file gives functions for creating and manipulating models.
 *    Models are used for rendering and collision detection.
 */
#pragma once

#include "libchik.h"

typedef struct {
    vec3_t aPos;
    vec3_t aRot;
    vec3_t aScale;

    trap_t aMesh;
} model_t;

/*
 *    Creates a model with raw vertex data.
 *
 *    @param void *         The raw vertex data.
 *    @param u32            The size of the vertex data.
 *    @param u32            The stride of the vertex data.
 *    @param v_layout_t     The layout of the vertex data.
 *
 *    @return model_t       The model.
 */
model_t model_create_raw( void *spVerts, u32 sSize, u32 sVStride, v_layout_t sLayout );

/*
 *    Creates a model and its mesh.
 *
 *    @param trap_t     The handle to the vertex buffer.
 *    @param trap_t     The handle to the texture.
 * 
 *    @return model_t     The model.
 */
model_t model_create( trap_t sVBuffer, trap_t sTexture );

/*
 *    Set's a model's mesh vertex data.
 *
 *    @param model_t       *    The model.
 *    @param trap_t           The handle to the vertex buffer.
 *
 *    @return u32               1 if successful, 0 otherwise.
 */
u32 model_set_mesh_vertex_buffer( model_t *spModel, trap_t sVBuffer );

/*
 *    Set's a model's mesh texture.
 *
 *    @param model_t *    The model.
 *    @param trap_t     The mesh texture.
 *
 *    @return u32         1 if successful, 0 otherwise.
 */
u32 model_set_mesh_texture( model_t *spModel, trap_t sTex );

/*
 *    Draws a model.
 *
 *    @param model_t *    The model.
 */
void model_draw( model_t *spModel );

/*
 *    Frees a model.
 *
 *    @param model_t *    The model.
 */
void model_free( model_t *spModel );