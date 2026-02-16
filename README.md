# MagicGame Setup

## Starting Steps
These steps are going to be the same no matter what operating system you run

- Clone the repository onto local machine into whatever directory you wish

```bash
git clone https://github.com/DisenchantmentDev/MagicGame.git MagicGame
```

## Windows
- Ensure you have a working installation of MSVC for C compilation.
    - To do this, go to [this link](https://visualstudio.microsoft.com/downloads/)
    - Scroll to the **All Downloads** section, and open **Tools for Visual Studio**
    - Download **Build Tools for Visual Studio** and run the installer
    - Add whatever you want, but you only need **Desktop development with C++** workload
    - Run that and you should be able to go
- Once MSVC is installed, open **Developer Command Prompt for VS 2022**
- Navigate to the directory of the game, and run the command:

```bash
cl nob.c
```

- Run `nob.exe` to compile the game proper
- This should output a working .exe of the game.

## Linux
- Make sure relevant libraries are downloaded
- Compile the `nob.c` file

```bash
gcc -o nob nob.c
```

- Run nob to compile

```bash
./nob
```

- Run the game
