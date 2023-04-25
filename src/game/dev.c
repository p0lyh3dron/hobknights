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

    void *v = vbuffer_create(&verts, sizeof(verts), sizeof(verts[0]), _v_layout);

    if (v == (void *)0x0) {
        LOGF_ERROR("Failed to create vertex buffer for dev cube.");
        return 0;
    }

    if (_dev_image == (image_t *)0x0) {
        _dev_image = image_create_from_file("assets/images/dev/noise.bmp", 69);
    }

    model_t *model = model_create_textured(v, _dev_image);

    unsigned int entity = entity_create();
    entity_add_transform(entity, nullptr, nullptr);
    entity_add_model(entity, model);

    return entity;
}