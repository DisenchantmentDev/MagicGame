# MagicGame Setup

## Starting Steps
These steps are going to be the same no matter what operating system you run

- Clone the repository onto local machine into whatever directory you wish

```bash
git clone https://github.com/DisenchantmentDev/MagicGame.git MagicGame
```

- Run the setup.sh script
    - If you are on windows, call the next command through git shell

```bash
bash setup.sh
```

- This should clone the relevant, most recent version of raylib into `/thirdparty/raylib` for building

## Windows
- Ensure you have a working installation of MSVC for C compilation.
    - You can do this with [this link](https://visualstudio.microsoft.com/vs/community/) for Visual Studio itself.
    - You can also download just the compiler and not the entirety of VS.
- You should be able to compile the `nob.c` file into a `nob.exe` with msvc
- Run `nob.exe` to compile the game proper
- This should output a working .exe of the game.

## Linux
- Make sure relevant libraries are downloaded
- Compile the `nob.c` file

```bash
gcc nob nob.c
```

- Run nob to compile

```bash
./nob
```

- Run the game
