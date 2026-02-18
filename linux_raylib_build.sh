#!/bin/bash

DIR_RAYLIB="./thirdparty/raylib"
URL_RAYLIB="https://github.com/raysan5/raylib.git"

if [ -d "$DIR_RAYLIB" ]; then
    echo "Removing $DIR_RAYLIB"
    rm -rf $DIR_RAYLIB
else
    echo "$DIR_RAYLIB doesn't exist, nothing to remove"
fi

git clone --depth 1 "$URL_RAYLIB" "$DIR_RAYLIB"

if [ $? -eq 0 ]; then
    echo "Raylib repo cloned successfully"
else
    echo "there was an issue cloning"
fi
