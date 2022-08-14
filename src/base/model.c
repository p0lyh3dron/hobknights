/*
 *    model.c    --    source for models
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 9th, 2022.
 * 
 *    This file is part of the Chik game base.
 * 
 *    This file defines the functions for creating and manipulating models.
 */
#include "model.h"

#include "base.h"

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
model_t model_create_raw( void *spVerts, u32 sSize, u32 sVStride, v_layout_t sLayout ) {
    model_t sModel;
    handle_t v = vbuffer_create( spVerts, sSize, sVStride, sLayout );
    if ( v == INVALID_HANDLE ) {
        log_error( "Could not create vertex buffer." );
        return sModel;
    }
    sModel.aMesh = mesh_create( v, INVALID_HANDLE );
    if ( sModel.aMesh == INVALID_HANDLE ) {
        log_error( "Could not create mesh." );
        return sModel;
    }
    return sModel;
}

/*
 *    Creates a model and its mesh.
 *
 *    @param handle_t     The handle to the vertex buffer.
 *    @param handle_t     The handle to the texture.
 * 
 *    @return model_t     The model.
 */
model_t model_create( handle_t sVBuffer, handle_t sTexture ) {
    model_t sModel;
    sModel.aMesh = mesh_create( sVBuffer, sTexture );
    if ( sModel.aMesh == INVALID_HANDLE ) {
        log_error( "Could not create mesh." );
        return sModel;
    }
    return sModel;
}

/*
 *    Set's a model's mesh vertex data.
 *
 *    @param model_t       *    The model.
 *    @param handle_t           The handle to the vertex buffer.
 *
 *    @return u32               1 if successful, 0 otherwise.
 */
u32 model_set_mesh_vertex_buffer( model_t *spModel, handle_t sVBuffer ) {
    if ( sVBuffer == INVALID_HANDLE ) {
        log_error( "Invalid vertex buffer handle." );
        return 0;
    }
    mesh_set_vertex_buffer( spModel->aMesh, sVBuffer );
    return 1;
}

/*
 *    Set's a model's mesh texture.
 *
 *    @param model_t *    The model.
 *    @param handle_t     The mesh texture.
 *
 *    @return u32         1 if successful, 0 otherwise.
 */
u32 model_set_mesh_texture( model_t *spModel, handle_t sTex ) {
    if ( sTex == INVALID_HANDLE ) {
        log_error( "Invalid texture handle." );
        return 0;
    }
    mesh_set_texture( spModel->aMesh, sTex );
    return 1;
}

/*
 *    Draws a model.
 *
 *    @param model_t *    The model.
 */
void model_draw( model_t *spModel ) {
    mesh_rotate( spModel->aRot );
    mesh_translate( spModel->aPos );
    mesh_scale( spModel->aScale );
    mesh_draw( spModel->aMesh );
}

/*
 *    Frees a model.
 *
 *    @param model_t *    The model.
 */
void model_free( model_t *spModel ) {
    mesh_free( spModel->aMesh );
}