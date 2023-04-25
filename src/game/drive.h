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