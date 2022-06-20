#ifndef HOBKNIGHTS_MAP_H
#define HOBKNIGHTS_MAP_H

#include "libchik.h"

#include "../base/base.h"

/*
 *    Creates a cube.
 *
 *    @param f32                 The size of the cube.
 * 
 *    @return chik_vertex_t *    The cube.
 */
chik_vertex_t *create_cube( f32 sSize );

/*
 *    Creates the test map.
 *
 *    @param  vec3_t    The center of the map.
 *    @param  f32       The size of the map.
 *
 *    @return u32       Entity id of the map.
 */
u32 map_test_create( vec3_t sCenter, f32 sSize );

#endif /* HOBKNIGHTS_MAP_H  */