#include "map.h"

#include "entity.h"
#include "../base/shader.h"

/*
 *    Creates a cube.
 *
 *    @param f32                 The size of the cube.
 * 
 *    @return chik_vertex_t *    The cube.
 */
chik_vertex_t *create_cube( f32 sSize ) {
    static chik_vertex_t pRet[ 36 ];

    chik_vertex_t pVertex[ 36 ] = {
        { { - sSize, - sSize,  - sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, + sSize,  - sSize, 1.f }, { 0.f, 1.f } },
        { { + sSize, + sSize,  - sSize, 1.f }, { 1.f, 1.f } },
        { { - sSize, - sSize,  - sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, - sSize,  - sSize, 1.f }, { 1.f, 0.f } },
        { { + sSize, + sSize,  - sSize, 1.f }, { 1.f, 1.f } },
        
        { { - sSize, - sSize,  + sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, + sSize,  + sSize, 1.f }, { 0.f, 1.f } },
        { { + sSize, + sSize,  + sSize, 1.f }, { 1.f, 1.f } },
        { { - sSize, - sSize,  + sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, - sSize,  + sSize, 1.f }, { 1.f, 0.f } },
        { { + sSize, + sSize,  + sSize, 1.f }, { 1.f, 1.f } },

        { { - sSize, - sSize,  + sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, + sSize,  + sSize, 1.f }, { 0.f, 1.f } },
        { { - sSize, + sSize,  - sSize, 1.f }, { 1.f, 1.f } },
        { { - sSize, - sSize,  + sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, - sSize,  - sSize, 1.f }, { 1.f, 0.f } },
        { { - sSize, + sSize,  - sSize, 1.f }, { 1.f, 1.f } },

        { { + sSize, - sSize,  + sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, + sSize,  + sSize, 1.f }, { 0.f, 1.f } },
        { { + sSize, + sSize,  - sSize, 1.f }, { 1.f, 1.f } },
        { { + sSize, - sSize,  + sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, - sSize,  - sSize, 1.f }, { 1.f, 0.f } },
        { { + sSize, + sSize,  - sSize, 1.f }, { 1.f, 1.f } },

        { { - sSize, - sSize,  - sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, - sSize,  + sSize, 1.f }, { 0.f, 1.f } },
        { { + sSize, - sSize,  + sSize, 1.f }, { 1.f, 1.f } },
        { { - sSize, - sSize,  - sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, - sSize,  - sSize, 1.f }, { 1.f, 0.f } },
        { { + sSize, - sSize,  + sSize, 1.f }, { 1.f, 1.f } },

        { { - sSize, + sSize,  - sSize, 1.f }, { 0.f, 0.f } },
        { { - sSize, + sSize,  + sSize, 1.f }, { 0.f, 1.f } },
        { { + sSize, + sSize,  + sSize, 1.f }, { 1.f, 1.f } },
        { { - sSize, + sSize,  - sSize, 1.f }, { 0.f, 0.f } },
        { { + sSize, + sSize,  - sSize, 1.f }, { 1.f, 0.f } },
        { { + sSize, + sSize,  + sSize, 1.f }, { 1.f, 1.f } },
    };
    memcpy( pRet, pVertex, sizeof( pVertex ) );

    return pRet;
}

/*
 *    Creates the test map.
 *
 *    @param  vec3_t    The center of the map.
 *    @param  f32       The size of the map.
 *
 *    @return u32       Entity id of the map.
 */
u32 map_test_create( vec3_t sCenter, f32 sSize ) {
    /*chik_vertex_t pVertex[ 36 ] = {
        { { sCenter.x - sSize, sCenter.y - sSize, sCenter.z - sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x - sSize, sCenter.y + sSize, sCenter.z - sSize, 1.f }, { 0.f, 1.f } },
        { { sCenter.x + sSize, sCenter.y + sSize, sCenter.z - sSize, 1.f }, { 1.f, 1.f } },
        { { sCenter.x - sSize, sCenter.y - sSize, sCenter.z - sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x + sSize, sCenter.y - sSize, sCenter.z - sSize, 1.f }, { 1.f, 0.f } },
        { { sCenter.x + sSize, sCenter.y + sSize, sCenter.z - sSize, 1.f }, { 1.f, 1.f } },
        
        { { sCenter.x - sSize, sCenter.y - sSize, sCenter.z + sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x - sSize, sCenter.y + sSize, sCenter.z + sSize, 1.f }, { 0.f, 1.f } },
        { { sCenter.x + sSize, sCenter.y + sSize, sCenter.z + sSize, 1.f }, { 1.f, 1.f } },
        { { sCenter.x - sSize, sCenter.y - sSize, sCenter.z + sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x + sSize, sCenter.y - sSize, sCenter.z + sSize, 1.f }, { 1.f, 0.f } },
        { { sCenter.x + sSize, sCenter.y + sSize, sCenter.z + sSize, 1.f }, { 1.f, 1.f } },

        { { sCenter.x - sSize, sCenter.y - sSize, sCenter.z + sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x - sSize, sCenter.y + sSize, sCenter.z + sSize, 1.f }, { 0.f, 1.f } },
        { { sCenter.x - sSize, sCenter.y + sSize, sCenter.z - sSize, 1.f }, { 1.f, 1.f } },
        { { sCenter.x - sSize, sCenter.y - sSize, sCenter.z + sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x - sSize, sCenter.y - sSize, sCenter.z - sSize, 1.f }, { 1.f, 0.f } },
        { { sCenter.x - sSize, sCenter.y + sSize, sCenter.z - sSize, 1.f }, { 1.f, 1.f } },

        { { sCenter.x + sSize, sCenter.y - sSize, sCenter.z + sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x + sSize, sCenter.y + sSize, sCenter.z + sSize, 1.f }, { 0.f, 1.f } },
        { { sCenter.x + sSize, sCenter.y + sSize, sCenter.z - sSize, 1.f }, { 1.f, 1.f } },
        { { sCenter.x + sSize, sCenter.y - sSize, sCenter.z + sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x + sSize, sCenter.y - sSize, sCenter.z - sSize, 1.f }, { 1.f, 0.f } },
        { { sCenter.x + sSize, sCenter.y + sSize, sCenter.z - sSize, 1.f }, { 1.f, 1.f } },

        { { sCenter.x - sSize, sCenter.y - sSize, sCenter.z - sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x - sSize, sCenter.y - sSize, sCenter.z + sSize, 1.f }, { 0.f, 1.f } },
        { { sCenter.x + sSize, sCenter.y - sSize, sCenter.z + sSize, 1.f }, { 1.f, 1.f } },
        { { sCenter.x - sSize, sCenter.y - sSize, sCenter.z - sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x + sSize, sCenter.y - sSize, sCenter.z - sSize, 1.f }, { 1.f, 0.f } },
        { { sCenter.x + sSize, sCenter.y - sSize, sCenter.z + sSize, 1.f }, { 1.f, 1.f } },

        { { sCenter.x - sSize, sCenter.y + sSize, sCenter.z - sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x - sSize, sCenter.y + sSize, sCenter.z + sSize, 1.f }, { 0.f, 1.f } },
        { { sCenter.x + sSize, sCenter.y + sSize, sCenter.z + sSize, 1.f }, { 1.f, 1.f } },
        { { sCenter.x - sSize, sCenter.y + sSize, sCenter.z - sSize, 1.f }, { 0.f, 0.f } },
        { { sCenter.x + sSize, sCenter.y + sSize, sCenter.z - sSize, 1.f }, { 1.f, 0.f } },
        { { sCenter.x + sSize, sCenter.y + sSize, sCenter.z + sSize, 1.f }, { 1.f, 1.f } },
    };*/

    chik_vertex_t verts[ 36 ];

    memcpy( verts, create_cube( sSize ), sizeof( verts ) );

    s64 i;
    for ( i = 0; i < ARR_LEN( verts ); ++i ) {
        verts[ i ].aPos.x += sCenter.x;
        verts[ i ].aPos.y += sCenter.y;
        verts[ i ].aPos.z += sCenter.z;
    }

    handle_t vbuffer = vbuffer_create( verts, sizeof( verts ), sizeof( verts[ 0 ] ), gVLayout );
    handle_t tex     = texture_create_from_file( "hobknights/assets/images/dev/noise.bmp", 69 );

    model_t model    = model_create( vbuffer, tex );

    u32 map = entity_create();
    entity_add_model( map, model );
    entity_add_transform( map, nullptr, nullptr );
    entity_add_driveable( map, nullptr );

    return map;
}