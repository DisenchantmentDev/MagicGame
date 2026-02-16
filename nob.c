#include <stdbool.h>

#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX

#include "./thirdparty/nob.h"

bool build_game(void);
bool build_raylib(void);
bool raylib_exists(void);

#if defined(linux) || defined(__linux) || defined(__linux__)
#include "./src_build/nob_linux.c"
#elif defined(WIN32) || defined(_WIN32) || defined(_MSC_VER)
#include "./src_build/nob_win64_msvc.c"
#else
#error "No target is defined."
#endif

static const char *raylib_modules[] = {
    "rcore", "raudio", "rmodels", "rtext", "rtextures", "utils",
};

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF_PLUS(argc, argv, "./src_build/nob_linux.c",
                               "./src_build/nob_win64_msvc.c");

    nob_log(INFO, "--- STAGE 1 ---");

    if (!mkdir_if_not_exists("build")) {
        return 1;
    }

    if (!raylib_exists()) {
        nob_log(INFO, "Building Raylib");
        build_raylib();
    }

    bool game = build_game();
    if (game) {
        nob_log(INFO, "Building on linux");
    } else {
        nob_log(INFO, "Building on Windows");
    }

    return 0;
}
