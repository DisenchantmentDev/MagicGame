# MagicGame Setup

## Starting Steps
These steps are going to be the same no matter what operating system you run

- Clone the repository onto local machine into whatever directory you wish

`git clone https://github.com/DisenchantmentDev/MagicGame.git MagicGame`

- Run the setup.sh script
    - If you are on windows, do this through the git shell

`bash setup.sh`

- Then clone raylib into the raylib folder

`git clone --depth 1 https://github.com/raysan5/raylib.git thirdparty/raylib`

## Windows
- Ensure you have a working installation of MSVC for C compilation.
    - You can do this with [this link](https://visualstudio.microsoft.com/vs/community/) for Visual Studio itself.
    - You can also download just the compiler and not the entirety of VS.
- You should be able to compile the `nob.c` file into a `nob.exe`
- Run `nob.exe` to compile the game proper
- This should output a working .exe of the game.

## Linux
- Make sure relevant libraries are downloaded
- Compile the `nob.c` file

`gcc nob nob.c`

- Run nob to compile

`./nob`

- Run the game
