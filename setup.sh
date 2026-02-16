#!/bin/bash

DIR_RAYLIB="./thirdparty/raylib/"
URL_RAYLIB="git clone --depth 1 https://github.com/raysan5/raylib.git"

# Check if Raylib already exists from a fresh pull of the game repo, and remove accordingly
if [ -d "$DIR_RAYLIB" ]; then
    echo "Removing $DIR_RAYLIB"
    rm -rf $DIR_RAYLIB
else
    echo "$DIR_RAYLIB does not exist, nothing to remove"
fi

# Clone the Raylib repository into the /thirdparty/raylib/ directory
git clone "$URL_RAYLIB" "$DIR_RAYLIB"

# Check if the clone was successful
if [ $? -eq 0 ]; then
    echo "Raylib repository cloned successfully"
else
    echo "There was an error cloning"
fi
