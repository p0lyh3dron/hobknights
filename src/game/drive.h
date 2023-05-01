#pragma once

#include "entity.h"

/*
 *    Sets the driven entity.
 *
 *    @param unsigned int    The entity id.
 */
void drive_set_driven_entity(unsigned int sId);

/*
 *    Drives the driven entity.
 */
void drive_drive_driven_entity();

/*
 *    Tells clip movement if the player is on the ground.
 *
 *    @param unsigned char    1 if the player is on the ground, 0 otherwise.
 */
void drive_set_on_ground(unsigned char grounded);