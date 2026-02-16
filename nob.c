#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX

#include "./thirdparty/nob.h"

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF_PLUS(argc, argv, "./thirdparty/nob.h");

  nob_log(INFO, "--- STAGE 1 ---");

  if (!mkdir_if_not_exists("build"))
    return 1;

  // TODO: basic nob build stuff, work on mingw and linux files specifically
  // TODO: .clang_format file because how this is formatted is driving me nuts

  return 0;
}
