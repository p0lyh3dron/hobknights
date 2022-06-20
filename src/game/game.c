#include "game.h"

#include "drive.h"
#include "entity.h"
#include "map.h"

s32 gPlayer = -1;

e_transform_t *gpPlayerPos = nullptr;
e_camera_t    *gpCamera    = nullptr;

handle_t gCam = INVALID_HANDLE;

s32 gLight1 = -1;
s32 gLight2 = -1;

/*
 *    Sets up the game.
 */
void game_setup( void ) {
    entity_setup();

    /*
     *    Create the player with a transform, driveable, and a camera.
     */
    gPlayer = entity_create();
    entity_add_transform( gPlayer, nullptr, nullptr );
    entity_add_driveable( gPlayer, nullptr );
    entity_add_camera( gPlayer, nullptr );

    u32 map = map_test_create( ( vec3_t ){ 0.f, 0.f, 0.f }, 4.f );

    chik_vertex_t vertices[ 36 ];
    memcpy( vertices, create_cube( 0.25f ), sizeof( vertices ) );
    handle_t vbuffer = vbuffer_create( vertices, sizeof( vertices ), sizeof( vertices[ 0 ] ), gVLayout );
    handle_t tex     = texture_create_from_file( "hobknights/assets/images/dev/noise.bmp", 69 );

    model_t model = model_create( vbuffer, tex );
    model.aRot = ( vec3_t ){ 69.f, 42.f, 0.f };

    gLight1 = entity_create();
    entity_add_transform( gLight1, nullptr, nullptr );
    entity_add_light( gLight1, ( vec3_t ){ 1.0f, 0.5f, 0.5f }, 0.5f );
    entity_add_model( gLight1, model );

    model.aRot = ( vec3_t ){ 0.f, 0.f, 0.f };
    gLight2 = entity_create();
    entity_add_transform( gLight2, nullptr, nullptr );
    entity_add_light( gLight2, ( vec3_t ){ 0.5f, 0.5f, 1.0f }, 1.0f );
    entity_add_model( gLight2, model );

    /*
     *    We'll hold on to these for now.
     */
    gpPlayerPos     = entity_get_transform( gPlayer );
    gpCamera        = entity_get_camera( gPlayer );

    /*
     *    Move the player from the center of the map.
     */
    gpCamera->aOriginOffset.y = 0.f;
    gpPlayerPos->aPosition.z   = -10.f;
    gpPlayerPos->aPosition.y   = 0.f;
    
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
    t += 0.01f;
    drive_drive_driven_entity();

    e_transform_t *pPos = entity_get_transform( gLight1 );
    pPos->aPosition.x = sinf( t ) * 10.f;
    pPos->aPosition.z = cosf( t ) * 10.f;
    pPos->aPosition.y = 0.f;

    pPos->aRotation.x = 42.f;
    pPos->aRotation.y = 42.f;

    pPos = entity_get_transform( gLight2 );
    pPos->aPosition.x = cosf( t ) * 10.f;
    pPos->aPosition.z = sinf( t ) * 10.f;
    pPos->aPosition.y = 0.f;

    vec3_t cam = { gpPlayerPos->aPosition.x + gpCamera->aOriginOffset.x,
                   gpPlayerPos->aPosition.y + gpCamera->aOriginOffset.y,
                   gpPlayerPos->aPosition.z + gpCamera->aOriginOffset.z };

    set_camera_position( gCam, cam );
    set_camera_direction( gCam, gpPlayerPos->aRotation );

    entity_update();
    threadpool_wait();
    draw_frame();
}

/*
 *    Tears down the game.
 */
void game_teardown( void ) {

}