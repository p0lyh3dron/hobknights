#include "map.h"

#include "dev.h"
#include "entity.h"

/*
 *    Creates the test map.
 *
 *    @param  vec3_t c     The center of the map.
 *    @param  float  s     The size of the map.
 *
 *    @return unsigned int       Entity id of the map.
 */
unsigned int map_test_create(vec3_t c, float s) {
    unsigned int map = dev_cube_create(s);

    e_transform_t *trans = entity_get_transform(map);
    trans->pos     = c;

    return map;
}