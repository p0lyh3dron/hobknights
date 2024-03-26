/*
 *    main.c    --    source for main.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file defines the entry point for Hobknights.
 */
#include "libchik.h"

#include <assert.h>
#include <math.h>
#include <string.h>

#include "../base/base.h"
#include "game.h"

int run(void) {
    filesystem_add_search_path("./hobknights/");
    app_init("Hobknights", (vec3s_t){0, 0, 0});

    if (!base_engine_init("./bin/chikengine", "./bin/chikgfx", "./bin/ch_core",
                          nullptr)) {
        log_fatal("Unable to initialize the engine!\n");
        return 0;
    }

    game_setup();

    while (base_engine_update()) {
        base_update_engine();
        game_update();
    }

    game_teardown();

    base_free_engine_resources();

    return 0;
}