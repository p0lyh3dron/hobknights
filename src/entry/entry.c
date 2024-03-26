/*
 *    entry.c    --    entry point for Chik engine games.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This source file loads the client and server ( if networked ),
 *    and then starts the game loop.
 */
#include "libchik.h"

#define PATH_MAX_LENGTH 1024

#include <string.h>

void print_help(void) {
    const char *exec = args_get_executable();

    printf("Usage: %s [options]\n", exec);
    printf("Options ( '*' means required ):\n");
    printf("  -h, --help                 Print this help message.\n");
    printf("* -g, --game <game>          The game to run.\n");
    printf("  -c, --client               Run as a client.\n");
    printf("  -s, --server               Run as a server.\n");
    printf("  -n, --network              Run as a client or server.\n");
    printf("  -p, --port <port>          Set the port to use.\n");
    printf("  -l, --log  <logfile>       Set the log file to use.\n");
    printf("  -d, --debug                Enable debug mode.\n");
    printf("  -v, --version              Print the version of Chik.\n");
}

/*
 *    Entry point for Chik engine games.
 *
 *    @param int        Number of arguments passed to the program.
 *    @param char **    Array of arguments passed to the program.
 *
 *    @return int       0 on success, 1 on failure.
 */
int main(const int argc, const char **argv) {
    args_init(argc, argv);
    shell_init();
    threadpool_init(256, 16);
    filesystem_init("./", "/", nullptr);
    log_open_file("./log.txt");

    dl_handle_t d    = 0;
    const char *game = 0;

    if (args_has("--help")) {
        print_help();
        return 0;
    }

    /*
     *    Check for game parameter.
     */
    if (args_has("-g") || args_has("--game")) {
        game = args_get_str("-g");

        if (game == NULL) {
            game = args_get_str("--game");
        }

        if (game != NULL) {
            char path[PATH_MAX_LENGTH];
            snprintf(path, PATH_MAX_LENGTH, "./%s/bin/%s%s", game, game,
                     DL_EXTENSION);

            d = dl_open(path);
        }
    } else {
        LOGF_FAT("No game specified.\n");
    }

    /*
     *    dl_open() failed.
     */
    if (d == 0) {
        VLOGF_FAT("Could not load game: %s.\n\ndl_error(): %s\n",
                  game, dl_error());
    }

    int (*run)(void) = 0;
    *(void **)(&run) = dl_sym(d, "run");

    /*
     *    dl_sym() failed.
     */
    if (run == 0) {
        VLOGF_FAT("Could not find run function in game: %s.\n\ndl_error(): %s\n",
                  game, dl_error());
    }

    int result = run();

    dl_close(d);
    log_close_file();

    return result;
}