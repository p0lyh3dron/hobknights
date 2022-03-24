/*
 *    framework.h    --    header file for declaring framework functions
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 * 
 *    This file is temporary as it is currently used for
 *    testing engine functionality, however the engine is
 *    currently in a very early stage of development.
 */
#pragma once

#include "libchik.h"
/*
 *    Draws the current frame.
 */
extern void ( *draw_frame )( void );
/*
 *    Draws a triangle to the screen.
 *
 *    @param chik_vec2_t    The first point of the triangle.
 *    @param chik_vec2_t    The second point of the triangle.
 *    @param chik_vec2_t    The third point of the triangle.
 */
extern void ( *draw_triangle )( chik_vec2_t a, chik_vec2_t b, chik_vec2_t c );

/*
 *    Initialize all functions used in the engine.
 *
 *    @return s32    1 on success, 0 on failure
 */
s32 framework_init( void );

/*
 *    Shutdown all functions used in the engine.
 */
void framework_shutdown( void );