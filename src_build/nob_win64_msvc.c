#include <stdio.h>

#define MAGICGAME_TARGET_NAME "win64-msvc"

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

    cmd.count = 0;
    nob_cmd_append(&cmd, "cl.exe");
    nob_cmd_append(&cmd, "/I", "./");
    nob_cmd_append(&cmd, "/I", RAYLIB_SRC_FOLDER);
    nob_cmd_append(&cmd, "cl.exe");
    nob_cmd_append(&cmd, "/I", "./");
    nob_cmd_append(&cmd, "/I", RAYLIB_SRC_FOLDER);
    nob_cmd_append(&cmd, "/Fobuild\\", "/Febuild\\musializer.exe");
    nob_cmd_append(&cmd,
                   "./src/main.c"); // add any further relevant source files
                                    // into this command. Example below:
    // nob_cmd_append(&cmd, "./src/musializer.c", "./src/plug.c",
    //                "./src/ffmpeg_windows.c",
    //                "./thirdparty/tinyfiledialogs.c");
    nob_cmd_append(
        &cmd, "/link", "/SUBSYSTEM:WINDOWS", "/entry:mainCRTStartup",
        nob_temp_sprintf("/LIBPATH:build/raylib/%s", MAGICGAME_TARGET_NAME),
        "raylib.lib");
    nob_cmd_append(&cmd, "Winmm.lib", "gdi32.lib", "User32.lib", "Shell32.lib",
                   "Ole32.lib", "comdlg32.lib", "./build/musializer.res");
    if (!nob_cmd_run_sync(cmd))
        nob_return_defer(false);

defer:
    nob_cmd_free(cmd);
    nob_da_free(procs);
    return result;
}

bool build_raylib(void) {
    bool result = true;
    Nob_Cmd cmd = {0};
    Nob_File_Paths object_files = {0};

    if (!nob_mkdir_if_not_exists("./build/raylib")) {
        nob_return_defer(false);
    }

    Nob_Procs procs = {0};

    const char *build_path =
        nob_temp_sprintf("./build/raylib/%s", MAGICGAME_TARGET_NAME);

    if (!nob_mkdir_if_not_exists(build_path)) {
        nob_return_defer(false);
    }

    for (size_t i = 0; i < NOB_ARRAY_LEN(raylib_modules); ++i) {
        const char *input_path =
            nob_temp_sprintf(RAYLIB_SRC_FOLDER"%s.c", raylib_modules[i]);
        const char *output_path =
            nob_temp_sprintf("%s%s.obj", build_path, raylib_modules[i]);

        nob_da_append(&object_files, output_path);

        if (nob_needs_rebuild(output_path, *input_path, 1)) {
            cmd.count = 0;
            nob_cmd_append(&cmd, "cl.exe", "/DPLATFORM_DESKTOP",
                           "/DSUPPORT_FILEFORMAT_FLAC=1");
            nob_cmd_append(&cmd, "/I",
                           RAYLIB_SRC_FOLDER"external/glfw/include");
            nob_cmd_append(&cmd, "/c", input_path);
            nob_cmd_append(&cmd, nob_temp_sprintf("/Fo%s", output_path));
            Nob_Proc proc = nob_cmd_run_async(cmd);
            nob_da_append(&procs, proc);
        }
    }
    cmd.count = 0;

    if (!nob_procs_wait(procs))
        nob_return_defer(false);

    if (nob_needs_rebuild("./build/raylib.dll", object_files.items,
                          object_files.count)) {
        nob_cmd_append(&cmd, "link.exe", "/DLL");
        for (size_t i = 0; i < NOB_ARRAY_LEN(raylib_modules); ++i) {
            const char *input_path =
                nob_temp_sprintf("%s/%s.obj", build_path, raylib_modules[i]);
            nob_cmd_append(&cmd, input_path);
        }
        nob_cmd_append(&cmd, "Winmm.lib", "gdi32.lib", "User32.lib",
                       "Shell32.lib");
        nob_cmd_append(&cmd,
                       nob_temp_sprintf("/IMPLIB:%s/raylib.lib", build_path));
        nob_cmd_append(&cmd, "/OUT:./build/raylib.dll");
        if (!nob_cmd_run_sync(cmd))
            nob_return_defer(false);
    }

defer:
    nob_cmd_free(cmd);
    nob_da_free(object_files);
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
