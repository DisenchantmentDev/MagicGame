#!/bin/bash

DIR_RAYLIB="./thirdparty/raylib/"

if [ -d "$DIR_RAYLIB" ]; then
    echo "Removing $DIR_RAYLIB"
    rm -rf $DIR_RAYLIB
else
    echo "$DIR_RAYLIB does not exist, nothing to remove"
fi
