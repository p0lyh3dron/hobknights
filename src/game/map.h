#ifndef HOBKNIGHTS_MAP_H
#define HOBKNIGHTS_MAP_H

#include "libchik.h"

#include "../base/base.h"

/*
 *    Creates the test map.
 *
 *    @param  vec3_t c      The center of the map.
 *    @param  float  s      The size of the map.
 *
 *    @return unsigned int       Entity id of the map.
 */
unsigned int map_test_create(vec3_t c, float s);

#endif /* HOBKNIGHTS_MAP_H  */