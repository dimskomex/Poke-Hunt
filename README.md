# Poke-Hunt!

## Game theme: 
* You're a pokeball who scores points by catching pokemon. If the pokemon is legendary, you earn 15 points, otherwise, 10 points. The goal is to collect as many points as you can by catching more and more pokemon.

* Catching pokemon is not that simple, as pokeball will rely on platforms that you will have to jump from one to the other, because the pokeball will fall down. If this is done, the game stops. This is not the only problem. A classic Pokeball isn't bound to catch all pokemon, so you'll need to try to catch it with great difficulty. As you catch pokemon and get more points, Pokeball upgrades. If the points exceed 20, it is upgraded to GreatBall, else if the points exceed 40, it is upgraded to UltraBall where it catches Pokemon with greater ease, and if they exceed 100, it becomes a MasterBall where it catches all Pokemon!

* Beware of red platforms, you have to be fast because they hide traps!

## Pokeball moves: 
      up key:                   jump 
      left key:                 slow right
      right key:                fast right
      no left or right key:     default right

## How to download the repository:
  You need to write in the terminal the command:

    git clone https://github.com/dimskomex/Poke-Hunt.git

## How to play:
- Linux: 
    1) You need to download the [gcc compiler](https://www.geeksforgeeks.org/how-to-install-gcc-compiler-on-linux/) 

    2) You need to go to the "Programs" folder by writing in the terminal:

            cd programs
    
    3) Finally, you have to write the command in the terminal:

            make run

- Windows:
    1) You need to download [Windows System Linux 1 or 2 (WSL)](https://learn.microsoft.com/en-us/windows/wsl/install) 
    2) You need to download [gcc compiler](https://www.systranbox.com/how-to-install-gcc-on-wsl-linux/)
    3) You need to download [VcXsrv](https://www.youtube.com/watch?v=4SZXbl9KVsw)
    4) Finally, you need to write these three commands in the terminal:
    
            cd programs
            export DISPLAY=:0
            make run

## to delete everything created by the Makefile:
write in the terminal the command:

    make clean

## Some comments
  * The game has memory leaks. This is due to the raylib library.
  * if you are using Visual Studio Code, you can run the program by pressing:

        ctrl + shift + b
      of course you must have downloaded all the necessary tools.

## About game:
- The game is based on the first task of the lesson [Data structures & programming techniques of the University of Athens](https://k08.chatzi.org/projects/project1/) and uses the [raylib graphics library](https://github.com/raysan5/raylib/blob/master/src/raylib.h).

- Many tools such as include files, modules & makefiles are based on the [Lecture Code repository](https://github.com/chatziko-k08/lecture-code).
