#ifndef HOBKNIGHTS_DEV_H
#define HOBKNIGHTS_DEV_H

#include "libchik.h"

extern image_t *_dev_image;

/*
 *    Create a developer cube entity with a model and transform.
 *
 *    @param float size     The size of the cube.
 *
 *    @return unsigned int    The entity ID of the cube.
 */
unsigned int dev_cube_create(float size);

#endif /* HOBKNIGHTS_DEV_H  */