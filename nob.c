#include <stdbool.h>

#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#define RAYLIB_SRC_FOLDER "thirdparty/raylib/src/"

#include "thirdparty/nob.h"

static const char *raylib_modules[] = {"rcore", "raudio", "rmodels", "rtext",
                                       "rtextures"};

#if defined(linux) || defined(__linux) || defined(__linux__)
#include "./src_build/nob_linux.c"
#elif defined(WIN32) || defined(_WIN32) || defined(_MSC_VER)
#include "./src_build/nob_win64_msvc.c"
#else
#error "No target is defined."
#endif

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF_PLUS(argc, argv, "./src_build/nob_linux.c",
                               "./src_build/nob_win64_msvc.c");

    nob_log(INFO, "--- STAGE 1 ---");

    if (!mkdir_if_not_exists("build")) {
        return 1;
    }

    nob_log(INFO, "Building Raylib");
    smol_build_raylib();

    build_game();

    return 0;
}
