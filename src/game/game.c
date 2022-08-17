#include "game.h"

#include "dev.h"
#include "drive.h"
#include "entity.h"
#include "map.h"
#include "shader.h"

s32 gPlayer = -1;

e_transform_t *gpPlayerPos = nullptr;
e_camera_t    *gpCamera    = nullptr;

trap_t gCam = INVALID_TRAP;

s32 gLight1 = -1;
s32 gLight2 = -1;

text_t gText = {};

/*
 *    Sets up the game.
 */
void game_setup( void ) {
    entity_setup();

    gText = text_init( "Text Test", BASE_TEXT_ALIGN_TOPRIGHT );
    text_set_position( &gText, ( vec2_t ){ 1.f, 1.f } );
    text_set_scale( &gText, ( vec2_t ){ 0.05f, 0.05f } );

    /*
     *    Create the player with a transform, driveable, and a camera.
     */
    gPlayer = entity_create();
    entity_add_transform( gPlayer, nullptr, nullptr );
    entity_add_driveable( gPlayer, nullptr );
    entity_add_camera( gPlayer, nullptr );

    u32 map = map_test_create( ( vec3_t ){ 0.f, 0.f, 0.f }, 4.f );

    gLight1 = dev_cube_create( 0.05f );
    gLight2 = dev_cube_create( 0.1f  );

    entity_add_light( gLight1, ( vec3_t ){ 1.0f, 0.5f, 0.5f }, 25.f );
    entity_add_light( gLight2, ( vec3_t ){ 0.5f, 0.5f, 1.0f }, 50.f );

    e_transform_t *pTrans = entity_get_transform( gLight1 );
    pTrans->aRotation     = ( vec2_t ){ 20.f, 0.f };
    
    pTrans = entity_get_transform( gLight2 );
    pTrans->aRotation     = ( vec2_t ){ 69.f, 42.f };
    /*
     *    We'll hold on to these for now.
     */
    gpPlayerPos     = entity_get_transform( gPlayer );
    gpCamera        = entity_get_camera( gPlayer );

    /*
     *    Move the player from the center of the map.
     */
    gpCamera->aOriginOffset.y = 0.f;
    gpPlayerPos->aPosition.z  = -10.f;
    gpPlayerPos->aPosition.y  = 0.f;
    gpPlayerPos->aRotation.y  = 0.f;
    
    gCam = create_camera();

    /*
     *    Set the camera to follow the player.
     */
    drive_set_driven_entity( gPlayer );
    
    set_camera_fov( gCam, 60.f );
    set_camera( gCam );
}

f32 t = 0.f;

/*
 *    Updates the game.
 */
void game_update( void ) {
    shader_begin( gCam );
    t += 0.05f;
    drive_drive_driven_entity();

    e_transform_t *pPos = entity_get_transform( gLight1 );
    pPos->aPosition.x = sinf( t ) * 1.f;
    pPos->aPosition.z = cosf( t ) * 1.f;
    pPos->aPosition.y = sinf( 0.33 * t ) * 1.5f;

    pPos->aRotation.x = 42.f;
    pPos->aRotation.y = 42.f;

    pPos = entity_get_transform( gLight2 );
    pPos->aPosition.x = cosf( t ) * 2.f;
    pPos->aPosition.z = sinf( t ) * 2.f;
    pPos->aPosition.y = sinf( 0.33 * t ) * -1.5f;

    vec3_t cam = { gpPlayerPos->aPosition.x + gpCamera->aOriginOffset.x,
                   gpPlayerPos->aPosition.y + gpCamera->aOriginOffset.y,
                   gpPlayerPos->aPosition.z + gpCamera->aOriginOffset.z };

    set_camera_position( gCam, cam );
    set_camera_direction( gCam, gpPlayerPos->aRotation );

    text_render( gText );
    entity_update();
   
    threadpool_wait();
    draw_frame();
}

/*
 *    Tears down the game.
 */
void game_teardown( void ) {

}