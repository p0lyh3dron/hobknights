#include "dev.h"

#include "../base/base.h"

#include "entity.h"
#include "shader.h"

image_t *_dev_image = (image_t *)0x0;

/*
 *    Create a developer cube entity with a model and transform.
 *
 *    @param float size     The size of the cube.
 *
 *    @return unsigned int    The entity ID of the cube.
 */
unsigned int dev_cube_create(float size) {
    vertex_t verts[36] = {
        {{-size, -size, -size, 1.f}, {0.f, 0.f}},
        {{-size, +size, -size, 1.f}, {0.f, 1.f}},
        {{+size, +size, -size, 1.f}, {1.f, 1.f}},
        {{-size, -size, -size, 1.f}, {0.f, 0.f}},
        {{+size, -size, -size, 1.f}, {1.f, 0.f}},
        {{+size, +size, -size, 1.f}, {1.f, 1.f}},

        {{-size, -size, +size, 1.f}, {0.f, 0.f}},
        {{-size, +size, +size, 1.f}, {0.f, 1.f}},
        {{+size, +size, +size, 1.f}, {1.f, 1.f}},
        {{-size, -size, +size, 1.f}, {0.f, 0.f}},
        {{+size, -size, +size, 1.f}, {1.f, 0.f}},
        {{+size, +size, +size, 1.f}, {1.f, 1.f}},

        {{-size, -size, +size, 1.f}, {0.f, 0.f}},
        {{-size, +size, +size, 1.f}, {0.f, 1.f}},
        {{-size, +size, -size, 1.f}, {1.f, 1.f}},
        {{-size, -size, +size, 1.f}, {0.f, 0.f}},
        {{-size, -size, -size, 1.f}, {1.f, 0.f}},
        {{-size, +size, -size, 1.f}, {1.f, 1.f}},

        {{+size, -size, +size, 1.f}, {0.f, 0.f}},
        {{+size, +size, +size, 1.f}, {0.f, 1.f}},
        {{+size, +size, -size, 1.f}, {1.f, 1.f}},
        {{+size, -size, +size, 1.f}, {0.f, 0.f}},
        {{+size, -size, -size, 1.f}, {1.f, 0.f}},
        {{+size, +size, -size, 1.f}, {1.f, 1.f}},

        {{-size, -size, -size, 1.f}, {0.f, 0.f}},
        {{-size, -size, +size, 1.f}, {0.f, 1.f}},
        {{+size, -size, +size, 1.f}, {1.f, 1.f}},
        {{-size, -size, -size, 1.f}, {0.f, 0.f}},
        {{+size, -size, -size, 1.f}, {1.f, 0.f}},
        {{+size, -size, +size, 1.f}, {1.f, 1.f}},

        {{-size, +size, -size, 1.f}, {0.f, 0.f}},
        {{-size, +size, +size, 1.f}, {0.f, 1.f}},
        {{+size, +size, +size, 1.f}, {1.f, 1.f}},
        {{-size, +size, -size, 1.f}, {0.f, 0.f}},
        {{+size, +size, -size, 1.f}, {1.f, 0.f}},
        {{+size, +size, +size, 1.f}, {1.f, 1.f}},
    };

    if (_dev_image == (image_t *)0x0)
        _dev_image = image_create_from_file("assets/images/dev/noise.bmp", 69);

    model_t *model = model_create_textured(&verts, sizeof(verts), sizeof(verts[0]), _v_layout, _dev_image);

    unsigned int entity = entity_create();
    entity_add_transform(entity, nullptr, nullptr);
    entity_add_model(entity, model);

    return entity;
}

/*
 *    Create a developer plane entity with a model and transform.
 *
 *    @param float size     The size of the plane.
 * 
 *    @return unsigned int    The entity ID of the plane.
 */
unsigned int dev_plane_create(float size) {
    vertex_t verts[6] = {
        {{-size, 0.f, -size, 1.f}, {0.f, 0.f}},
        {{-size, 0.f, +size, 1.f}, {0.f, 1.f}},
        {{+size, 0.f, +size, 1.f}, {1.f, 1.f}},
        {{-size, 0.f, -size, 1.f}, {0.f, 0.f}},
        {{+size, 0.f, -size, 1.f}, {1.f, 0.f}},
        {{+size, 0.f, +size, 1.f}, {1.f, 1.f}},
    };

    if (_dev_image == (image_t *)0x0)
        _dev_image = image_create_from_file("assets/images/dev/noise.bmp", 69);

    model_t *model = model_create_textured(&verts, sizeof(verts), sizeof(verts[0]), _v_layout, _dev_image);

    unsigned int entity = entity_create();
    entity_add_transform(entity, nullptr, nullptr);
    entity_add_model(entity, model);

    return entity;
}