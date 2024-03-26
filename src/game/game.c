#include "game.h"

#include "dev.h"
#include "drive.h"
#include "entity.h"
#include "map.h"
#include "shader.h"

#include "blade.h"

int _player;

e_transform_t *_player_pos;
e_camera_t    *_camera;
e_model_t     *_map;
e_driveable_t *_player_drive;

e_model_t *_riverhouse;

void *_cam;
void *_mus;

int _light_1;
int _light_2;


/*
 *    Sets up the game.
 */
void game_setup(void) {
    shell_variable_t variables[] = {
        {"e_timescale", "The timescale of the rotating blocks.", "0.05",
         nullptr, SHELL_VAR_FLOAT},
        {"hk_lighting", "Whether or not to do lighting calculations.", "true",
         shader_do_lighting, SHELL_VAR_BOOL},
        {nullptr, nullptr, nullptr, nullptr, SHELL_VAR_NONE}};

    shell_register_variables(variables);

    entity_setup();

    /*
     *    Create the player with a transform, driveable, and a camera.
     */
    _player = entity_create();
    entity_add_transform(_player, nullptr, nullptr);
    entity_add_driveable(_player, nullptr);
    entity_add_camera(_player, nullptr);

    unsigned int map = map_test_create((vec3_t){0.f, 0.f, 0.f}, 16.f);
    _map = entity_get_model(map);

    _light_1 = dev_cube_create(0.05f);
    _light_2 = dev_cube_create(0.1f);

    if (args_has("-riverhouse"))
        _riverhouse = entity_get_model(dev_riverhouse());

    entity_add_light(_light_1, (vec3_t){1.0f, 0.5f, 0.5f}, 200.f);
    entity_add_light(_light_2, (vec3_t){0.5f, 0.5f, 1.0f}, 400.f);

    e_transform_t *trans = entity_get_transform(_light_1);
    trans->rot     = (vec2_t){20.f, 0.f};

    trans            = entity_get_transform(_light_2);
    trans->rot = (vec2_t){69.f, 42.f};
    /*
     *    We'll hold on to these for now.
     */
    _player_pos = entity_get_transform(_player);
    _camera     = entity_get_camera(_player);

    /*
     *    Move the player from the center of the map.
     */
    _camera->origin_offset.y = 1.f;
    _player_pos->pos.z = -13.f;
    _player_pos->pos.y = 5.f;
    _player_pos->pos.x = 8.f;
    _player_pos->rot.y = 0.5f;
    _player_pos->rot.x = -0.5f;

    _cam = create_camera();

    /*
     *    Set the camera to follow the player.
     */
    drive_set_driven_entity(_player);
    _player_drive = entity_get_driveable(_player);

    set_camera_fov(_cam, 60.f);
    set_camera(_cam);

    _mus = audio_create_from_file("assets/music/edamame.wav", true);
    audio_play(_mus);

    image_t *bb = *(image_t **)rendertarget_get_backbuffer();

    blade_set_render_target(bb->buf, bb->width, bb->height);
}

float t = 0.f;

/*
 *    Updates the game.
 */
void game_update(void) {
    shader_begin(_cam);
    t += shell_get_variable("e_timescale").f;
    drive_drive_driven_entity();

    vec3_t collide = collision_cylinder_model(_player_pos->pos, 0.5f, 0.5f, _map->model);

    if (collide.x != 0.f || collide.y != 0.f || collide.z != 0.f) {
        _player_pos->pos.x += collide.x;
        _player_pos->pos.y += collide.y;
        _player_pos->pos.z += collide.z;

        _player_drive->velocity.x = -collide.x;
        _player_drive->velocity.y = -collide.y;
        _player_drive->velocity.z = -collide.z;

        if (collide.y > 0.f && (collide.x == 0.f && collide.z == 0.f))
            drive_set_on_ground(true);
        else
            drive_set_on_ground(false);
    } else {
        drive_set_on_ground(false);
    }

    e_transform_t *pos = entity_get_transform(_light_1);
    pos->pos.x   = sinf(t) * 12.f;
    pos->pos.z   = cosf(t) * 12.f;
    pos->pos.y   = -3.5f;

    pos->rot.x = 42.f;
    pos->rot.y = 42.f;

    pos              = entity_get_transform(_light_2);
    pos->pos.x = cosf(t) * 12.f;
    pos->pos.z = sinf(t) * 12.f;
    pos->pos.y = -3.5f;

    vec3_t cam = {_player_pos->pos.x + _camera->origin_offset.x,
                  _player_pos->pos.y + _camera->origin_offset.y,
                  _player_pos->pos.z + _camera->origin_offset.z};

    set_camera_position(_cam, cam);
    set_camera_direction(_cam, _player_pos->rot);

    audio_set_listener_position(_mus, (vec3_t){5.f, 0.f, 0.f}, _player_pos->pos, _player_pos->rot);

    entity_update();

    begin_render_group();

    //threadpool_wait();
    //blade_draw_config();
    draw_frame();
}

/*
 *    Tears down the game.
 */
void game_teardown(void) {}