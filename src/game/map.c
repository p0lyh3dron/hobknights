#include "map.h"

#include "dev.h"
#include "entity.h"

/*
 *    Creates the test map.
 *
 *    @param  vec3_t    The center of the map.
 *    @param  f32       The size of the map.
 *
 *    @return u32       Entity id of the map.
 */
u32 map_test_create( vec3_t sCenter, f32 sSize ) {
    u32 map = dev_cube_create( sSize );

    e_transform_t *pTrans = entity_get_transform( map );
    pTrans->aPosition = sCenter;

    return map;
}