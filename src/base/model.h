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
    vec3_t pos;
    vec3_t aRot;
    vec3_t scale;

    void *mesh;
} model_t;

/*
 *    Creates a model with raw vertex data.
 *
 *    @param void *vert           The raw vertex data.
 *    @param unsigned int size             The size of the vertex data.
 *    @param unsigned int stride           The stride of the vertex data.
 *    @param v_layout_t layout    The layout of the vertex data.
 *
 *    @return model_t *      The model.
 */
model_t *model_create_raw(void *vert, unsigned int size, unsigned int stride,
                          v_layout_t layout);

/*
 *    Creates a model and its mesh.
 *
 *    @param void    *v     The vertex buffer.
 *    @param image_t *i     The texture.
 *
 *    @return model_t *    The model.
 */
model_t *model_create_textured(void *v, image_t *i);

/*
 *    Set's a model's mesh vertex data.
 *
 *    @param model_t *model     The model.
 *    @param void *v            The handle to the vertex buffer.
 *
 *    @return unsigned int               1 if successful, 0 otherwise.
 */
unsigned int model_set_vbuffer(model_t *model, void *v);

/*
 *    Set's a model's mesh image.
 *
 *    @param model_t *model    The model.
 *    @param image_t *i        The image.
 *
 *    @return unsigned int         1 if successful, 0 otherwise.
 */
unsigned int model_set_mesh_image(model_t *model, image_t *i);

/*
 *    Draws a model.
 *
 *    @param model_t *model    The model.
 */
void model_draw(model_t *model);

/*
 *    Frees a model.
 *
 *    @param model_t *model    The model.
 */
void model_free(model_t *model);