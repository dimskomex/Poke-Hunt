# Poke-Hunt!

## Game theme: 
You're basically a pokeball who scores points by catching pokemon. If the pokemon is legendary, you earn 15 points, otherwise, 10 points. The goal is to collect as many points as you can by catching more and more pokemon. Catching pokemon is not that simple, as pokeball will rely on platforms that you will have to jump from one to the other, because the pokeball will fall down. If this is done, the game stops.

## Pokeball moves: 
The pokeball only moves to the right, but the speed changes depending on the keys. If you don't press any keys, it moves at normal speed, if you press the left key it goes slowly, while with the right key it goes fast. With the up key it jumps so that you go from one platform to another.

## How to play:
- Linux: 
    1) You need to download the [gcc compiler](https://www.geeksforgeeks.org/how-to-install-gcc-compiler-on-linux/) 

    2) You need to go to the "Programs" folder by writing in the terminal:
    -------------- 
      cd programs
    
    3) Finally, you have to write the command in the terminal:
    -------------- 
      make run

- Windows:
    1) You need to download [Windows System Linux 1 or 2 (WSL)](https://learn.microsoft.com/en-us/windows/wsl/install) 
    2) You need to download [gcc compiler](https://www.systranbox.com/how-to-install-gcc-on-wsl-linux/)
    3) You need to download [VcXsrv](https://www.youtube.com/watch?v=4SZXbl9KVsw)
    4) Finally, you need to write these three commands in the terminal:
    -------------- 
      cd programs
      export DISPLAY=:0
      make run

## Did you stop? Write in terminal:
    make clean

## About game:
- The game is based on the first task of the lesson [Data structures & programming techniques of the University of Athens](https://k08.chatzi.org/projects/project1/) and uses the [raylib graphics library](https://github.com/raysan5/raylib/blob/master/src/raylib.h)

- Many tools such as include files, modules & makefiles are based on the [Lecture Code repository](https://github.com/chatziko-k08/lecture-code)