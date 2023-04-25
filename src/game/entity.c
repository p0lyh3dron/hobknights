#include "entity.h"

#include "shader.h"

entity_flag_e _entity_flags[MAX_ENTITIES] = {0};

e_transform_t _transforms[MAX_ENTITIES] = {0};
e_driveable_t _driveables[MAX_ENTITIES] = {0};
e_camera_t    _cameras[MAX_ENTITIES]    = {0};
e_light_t     _lights[MAX_ENTITIES]     = {0};
e_model_t     _models[MAX_ENTITIES]     = {0};

/*
 *    Sets up entity system.
 */
void entity_setup(void) {
    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++) {
        _entity_flags[i]    = ENTITY_NONE;
        _transforms[i].id = -1;
        _driveables[i].id = -1;
        _cameras[i].id    = -1;
        _lights[i].id     = -1;
        _models[i].id      = -1;
    }
}

/*
 *    Creates an entity.
 *
 *    @return unsigned int    The entity id, 0 if failed.
 */
unsigned int entity_create(void) {
    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++) {
        if (_entity_flags[i] == ENTITY_NONE) {
            _entity_flags[i] = ENTITY_PRESENT;
            return i;
        }
    }
    return 0;
}

/*
 *    Adds a transform component to an entity.
 *
 *    @param unsigned int id        The entity id.
 *    @param vec3_t      *pos       The position.
 *    @param vec2_t      *rot       The rotation.
 *
 *    @return unsigned int        1 if the component was added, 0 if not.
 */
unsigned int entity_add_transform(unsigned int id, vec3_t *pos, vec2_t *rot) {
    if (_entity_flags[id] != ENTITY_PRESENT)
        return 0;

    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++) {
        if (_transforms[i].id == -1) {
            _transforms[i].id = id;
            if (pos == (vec3_t *)0x0)
                _transforms[i].pos = (vec3_t){0.f, 0.f, 0.f};
            else
                _transforms[i].pos = *pos;

            if (rot == (vec2_t *)0x0)
                _transforms[i].rot = (vec2_t){0.f, 0.f};
            else
                _transforms[i].rot = *rot;

            _transforms[i].scale = (vec3_t){1.f, 1.f, 1.f};
            return 1;
        }
    }

    return 0;
}

/*
 *    Returns a transform component from an entity.
 *
 *    @param unsigned int id                The entity id.
 *
 *    @return e_transform_t *    The transform component, NULL if not found.
 */
e_transform_t *entity_get_transform(unsigned int id) {
    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++)
        if (_transforms[i].id == id)
            return &_transforms[i];

    return (e_transform_t *)0x0;
}

/*
 *    Adds a driveable component to an entity.
 *
 *    @param unsigned int           id         The entity id.
 *    @param e_drivable_movetype_e *move_type  The move type.
 *
 *    @return unsigned int                     1 if the component was added, 0 if not.
 */
unsigned int entity_add_driveable(unsigned int id, e_drivable_movetype_e *move_type) {
    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++) {
        if (_driveables[i].id == -1) {
            _driveables[i].id = id;
            if (move_type == (e_drivable_movetype_e *)0x0)
                _driveables[i].move_type = DRIVE_NOCLIP;
            else
                _driveables[i].move_type = *move_type;

            return 1;
        }
    }
    return 0;
}

/*
 *    Returns a driveable component from an entity.
 *
 *    @param unsigned int id                The entity id.
 *
 *    @return e_driveable_t *    The driveable component, NULL if not found.
 */
e_driveable_t *entity_get_driveable(unsigned int id) {
    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++)
        if (_driveables[i].id == id)
            return &_driveables[i];

    return (e_driveable_t *)0x0;
}

/*
 *    Adds a camera component to an entity.
 *
 *    @param unsigned int id               The entity id.
 *    @param vec3_t      *origin_offset    The origin offset.
 *
 *    @return unsigned int        1 if the component was added, 0 if not.
 */
unsigned int entity_add_camera(unsigned int id, vec3_t *origin_offset) {
    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++) {
        if (_cameras[i].id == -1) {
            _cameras[i].id = id;
            if (origin_offset == (vec3_t *)0x0)
                _cameras[i].origin_offset = (vec3_t){0.f, 0.f, 0.f};
            else
                _cameras[i].origin_offset = *origin_offset;

            return 1;
        }
    }

    return 0;
}

/*
 *    Returns a camera component from an entity.
 *
 *    @param unsigned int id        The entity id.
 *
 *    @return e_camera_t *    The camera component, NULL if not found.
 */
e_camera_t *entity_get_camera(unsigned int id) {
    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++)
        if (_cameras[i].id == id)
            return &_cameras[i];

    return (e_camera_t *)0x0;
}

/*
 *    Adds a light component to an entity.
 *
 *    @param unsigned int id         The entity id.
 *    @param vec3_t       color      The color.
 *    @param float        intensity  The intensity.
 *
 *    @return unsigned int        1 if the component was added, 0 if not.
 */
unsigned int entity_add_light(unsigned int id, vec3_t color, float intensity) {
    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++) {
        if (_lights[i].id == -1) {
            _lights[i].id        = id;
            _lights[i].color      = color;
            _lights[i].intensity = intensity;
            return 1;
        }
    }

    return 0;
}

/*
 *    Returns a light component from an entity.
 *
 *    @param unsigned int id        The entity id.
 *
 *    @return e_light_t *    The light component, NULL if not found.
 */
e_light_t *entity_get_light(unsigned int id) {
    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++)
        if (_lights[i].id == id)
            return &_lights[i];

    return (e_light_t *)0x0;
}

/*
 *    Adds a model component to an entity.
 *
 *    @param unsigned int id            The entity id.
 *    @param model_t     *model         The model.
 *
 *    @return unsigned int        1 if the component was added, 0 if not.
 */
unsigned int entity_add_model(unsigned int id, model_t *model) {
    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++) {
        if (_models[i].id == -1) {
            _models[i].id    = id;
            _models[i].model = model;
            return 1;
        }
    }

    return 0;
}

/*
 *    Returns a model component from an entity.
 *
 *    @param unsigned int id        The entity id.
 *
 *    @return e_model_t *    The model component, NULL if not found.
 */
e_model_t *entity_get_model(unsigned int id) {
    unsigned long i;
    for (i = 0; i < MAX_ENTITIES; i++)
        if (_models[i].id == id)
            return &_models[i];

    return (e_model_t *)0x0;
}

/*
 *    Removes an entity.
 *
 *    @param unsigned int id   The entity id.
 */
void entity_remove(unsigned int id) { _entity_flags[id] = ENTITY_NONE; }

/*
 *    Updates all entities.
 */
void entity_update(void) {
    long i;
    for (i = 0; i < MAX_ENTITIES; i++) {
        if (_entity_flags[i] == ENTITY_PRESENT) {
            e_model_t     *model = entity_get_model(i);
            e_transform_t *trans = entity_get_transform(i);
            if (model != nullptr) {
                if (trans) {
                    model->model->pos   = trans->pos;
                    model->model->aRot  = (vec3_t){trans->rot.x, trans->rot.y};
                    model->model->scale = trans->scale;

                    shader_set_position(&model->model->pos);
                    shader_set_rotation(&model->model->aRot);
                    shader_set_scale(&model->model->scale);
                } else {
                    shader_set_position(nullptr);
                    shader_set_rotation(nullptr);
                    shader_set_scale(nullptr);
                }
                model_draw(model->model);
            }
        }
    }
}