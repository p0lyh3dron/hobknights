#include "dev.h"

#include "../base/base.h"

#include "entity.h"
#include "shader.h"

/*
 *    Create a developer cube entity with a model and transform.
 *
 *    @param f32     The size of the cube.
 * 
 *    @return u32    The entity ID of the cube.
 */
u32 dev_cube_create( f32 sSize ) {
    chik_vertex_t pVertex[ 36 ] = {
        { { - sSize, - sSize, - sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, + sSize, - sSize, 1.f }, { 0.f, 1.f } },
        { { + sSize, + sSize, - sSize, 1.f }, { 1.f, 1.f } },
        { { - sSize, - sSize, - sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, - sSize, - sSize, 1.f }, { 1.f, 0.f } },
        { { + sSize, + sSize, - sSize, 1.f }, { 1.f, 1.f } },
        
        { { - sSize, - sSize, + sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, + sSize, + sSize, 1.f }, { 0.f, 1.f } },
        { { + sSize, + sSize, + sSize, 1.f }, { 1.f, 1.f } },
        { { - sSize, - sSize, + sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, - sSize, + sSize, 1.f }, { 1.f, 0.f } },
        { { + sSize, + sSize, + sSize, 1.f }, { 1.f, 1.f } },

        { { - sSize, - sSize, + sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, + sSize, + sSize, 1.f }, { 0.f, 1.f } },
        { { - sSize, + sSize, - sSize, 1.f }, { 1.f, 1.f } },
        { { - sSize, - sSize, + sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, - sSize, - sSize, 1.f }, { 1.f, 0.f } },
        { { - sSize, + sSize, - sSize, 1.f }, { 1.f, 1.f } },

        { { + sSize, - sSize, + sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, + sSize, + sSize, 1.f }, { 0.f, 1.f } },
        { { + sSize, + sSize, - sSize, 1.f }, { 1.f, 1.f } },
        { { + sSize, - sSize, + sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, - sSize, - sSize, 1.f }, { 1.f, 0.f } },
        { { + sSize, + sSize, - sSize, 1.f }, { 1.f, 1.f } },

        { { - sSize, - sSize, - sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, - sSize, + sSize, 1.f }, { 0.f, 1.f } },
        { { + sSize, - sSize, + sSize, 1.f }, { 1.f, 1.f } },
        { { - sSize, - sSize, - sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, - sSize, - sSize, 1.f }, { 1.f, 0.f } },
        { { + sSize, - sSize, + sSize, 1.f }, { 1.f, 1.f } },

        { { - sSize, + sSize, - sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, + sSize, + sSize, 1.f }, { 0.f, 1.f } },
        { { + sSize, + sSize, + sSize, 1.f }, { 1.f, 1.f } },
        { { - sSize, + sSize, - sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, + sSize, - sSize, 1.f }, { 1.f, 0.f } },
        { { + sSize, + sSize, + sSize, 1.f }, { 1.f, 1.f } },
    };

    handle_t vbuffer = vbuffer_create( &pVertex, sizeof( pVertex ), sizeof( pVertex[ 0 ] ), gVLayout );
    handle_t tex     = texture_create_from_file( "assets/images/dev/noise2.bmp", 69 );

    model_t model = model_create( vbuffer, tex );

    u32 entity    = entity_create();
    entity_add_transform( entity, nullptr, nullptr );
    entity_add_model( entity, model );

    return entity;
}