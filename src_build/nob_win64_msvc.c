#include <stdio.h>

#define MAGICGAME_TARGET_NAME "win64-msvc"
#define MAGICGAME_WIN64_DIR "thirdparty\\raylib\\win64_msvc"

bool build_game(void) {
    bool result = true;
    Nob_Cmd cmd = {0};
    Nob_Procs procs = {0};

    /*At some point we want to set up a .rc file in src to call. Stores icons
     * and stuff */
    /* cmd.count = 0
     * nob_cmd_append(&cmd, "rc");
     * nob_cmd_append(&cmd, "/fo", "./build/{gamename}.res");
     * nob_cmd_append(&cmd, "./src/{gamename}.rc");
     * if (!nob_cmd_run_cync(cmd)) nob_return_defer(false);
     */

    // cmd.count = 0;
    nob_cmd_append(
        &cmd, "cl.exe", "/MD",
        "src/main.c", /* add any other source files here */
        "/I", nob_temp_sprintf("%s\\include", MAGICGAME_WIN64_DIR), "/I",
        "src/include", "/Fobuild\\", "/Febuild\\magic_game.exe", "/link",
        nob_temp_sprintf("/LIBPATH:%s\\lib", MAGICGAME_WIN64_DIR), "raylib.lib",
        "User32.lib", "gdi32.lib", "Winmm.lib", "Shell32.lib", "opengl32.lib");

    if (!nob_cmd_run_sync(cmd))
        nob_return_defer(false);

defer:
    nob_cmd_free(cmd);
    nob_da_free(procs);
    return result;
}

bool raylib_exists(void) {
    const char *build_path =
        temp_sprintf("./build/raylib/%s/rcore.o", MAGICGAME_TARGET_NAME);
    FILE *file;
    if ((file = fopen(build_path, "r"))) {
        fclose(file);
        return true;
    }
    return false;
}
