// TODO: write this full nob implementation
#include <unistd.h>

#define MAGICGAME_TARGET_NAME "linux"
#define MAGICGAME_LINUX_DIR "./thirdparty/raylib/linux/"

bool build_game(void) {
    bool result = true;
    Cmd cmd = {0};
    Procs procs = {0};

    cmd_append(&cmd, "gcc", "src/main.c", /* add any further files we add here. Can probably export into it's own loop */
               "-I"MAGICGAME_LINUX_DIR"include/", "-L", MAGICGAME_LINUX_DIR"lib", "-l:libraylib.a", "-o", 
               "./build/magic_game", "-lm", "-lpthread", "-ldl", "-lrt", "-lX11");

    if (!cmd_run(&cmd))
        return_defer(false);

defer:
    cmd_free(cmd);
    da_free(procs);
    return result;
}

bool raylib_exists(void) {
    const char *build_path =
        temp_sprintf("%slib/libraylib.a", MAGICGAME_LINUX_DIR);
    if (access(build_path, F_OK) == 0) {
        return true;
    }
    return false;
}
