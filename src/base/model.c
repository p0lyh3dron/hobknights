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
 *    @param void *vert           The raw vertex data.
 *    @param unsigned int size             The size of the vertex data.
 *    @param unsigned int stride           The stride of the vertex data.
 *    @param v_layout_t layout    The layout of the vertex data.
 *
 *    @return model_t *      The model.
 */
model_t *model_create_raw(void *vert, unsigned int size, unsigned int stride,
                          v_layout_t layout) {
    model_t *model = (model_t *)malloc(sizeof(model_t));

    if (model == (model_t *)0x0) {
        LOGF_ERR("Could not allocate model.\n");
        return model;
    }

    void *v = vbuffer_create(vert, size, stride, layout);

    if (v == (void *)0x0) {
        LOGF_ERR("Could not create vertex buffer.\n");
        return (model_t *)0x0;
    }

    model->mesh = mesh_create(v);

    if (model->mesh == (void *)0x0) {
        LOGF_ERR("Could not create mesh.");
        return (model_t *)0x0;
    }

    return model;
}

/*
 *    Creates a model and its mesh.
 *
 *    @param void    *v     The vertex buffer.
 *    @param image_t *i     The texture.
 *
 *    @return model_t *    The model.
 */
model_t *model_create_textured(void *v, image_t *i) {
    model_t *model = (model_t *)malloc(sizeof(model_t));

    if (model == (model_t *)0x0) {
        LOGF_ERR("Could not allocate model.\n");
        return (model_t *)0x0;
    }

    model->mesh = mesh_create(v);

    if (model->mesh == (void *)0x0) {
        LOGF_ERR("Could not create mesh.\n");
        return (model_t *)0x0;
    }

    mesh_append_asset(model->mesh, (void *)&i, sizeof(image_t *));

    return model;
}

/*
 *    Set's a model's mesh vertex data.
 *
 *    @param model_t *model     The model.
 *    @param void *v            The handle to the vertex buffer.
 *
 *    @return unsigned int               1 if successful, 0 otherwise.
 */
unsigned int model_set_vbuffer(model_t *model, void *v) {
    if (model == (model_t *)0x0) {
        LOGF_ERR("Invalid model handle.\n");
        return 0;
    }

    if (v == (void *)0x0) {
        LOGF_ERR("Invalid vertex buffer handle.\n");
        return 0;
    }

    mesh_set_vbuffer(model->mesh, v);

    return 1;
}

/*
 *    Set's a model's mesh image.
 *
 *    @param model_t *model    The model.
 *    @param image_t *i        The image.
 *
 *    @return unsigned int         1 if successful, 0 otherwise.
 */
unsigned int model_set_mesh_image(model_t *model, image_t *i) {
    if (model == (model_t *)0x0) {
        LOGF_ERR("Invalid model handle.\n");
        return 0;
    }

    if (i == (image_t *)0x0) {
        LOGF_ERR("Invalid texture handle.\n");
        return 0;
    }

    mesh_append_asset(model->mesh, (void *)i, sizeof(image_t *));

    return 1;
}

/*
 *    Draws a model.
 *
 *    @param model_t *model    The model.
 */
void model_draw(model_t *model) {
    mesh_draw(model->mesh);
}

/*
 *    Frees a model.
 *
 *    @param model_t *model    The model.
 */
void model_free(model_t *model) {
    mesh_free(model->mesh);
    free(model);
}