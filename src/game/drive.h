#pragma once

#include "entity.h"

/*
 *    Sets the driven entity.
 *
 *    @param u32    The entity id.
 */
void drive_set_driven_entity( u32 sId );

/*
 *    Drives the driven entity.
 */
void drive_drive_driven_entity();