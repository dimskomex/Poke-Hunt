# Poke-Hunt!

## Game theme: 
* You're a Pokeball who scores points by catching Pokemon. 

      Classic Pokemon:      5 points
      Iconic Pokemon:       10 points
      Legendary Pokemon:    15 points

  The goal is to collect as many points as you can by catching more and more pokemon.
  
* Classic Pokemon list:
  
      Staryu
      Hypno
      Starmie
      Gengar
      Snorlax
      Torterra
      Wobbuffet
      Azumarill

* Iconic Pokemon list:

      Gyarados
      Bulbasaur
      Charmander
      Picachu
      Squirtle
      Eevee
      Lucario

* Legendary Pokemon list:

      Mewtwo
      Reshiram
      Arceus
      Reyquaza
      Zekrom



* Catching Pokemon is not that simple, as Pokeball will rely on platforms that you will have to jump from one to the other, because the Pokeball will fall down. If this is done, the game stops. This is not the only problem. A classic Pokeball can't catch all Pokemon with ease (especially legendary ones). So you have to do a lot of collisions with Pokémon to get points. As you accumulate points, Pokeball is upgraded to GreatBall, UltraBall and TimerBall which can catch Pokémon more easily. The final stage is the MasterBall, which can catch all Pokemon directly!

      score <= 20:                    Classic Pokeball
      score > 20 and score <= 40:     GreatBall
      score > 40 and score <= 80:     UltraBall
      score > 80 and score <= 120:    TimerBall
      score > 120:                    MasterBall

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

## About game:
- The game is based on the first task of the lesson [Data structures & programming techniques of the University of Athens](https://k08.chatzi.org/projects/project1/) and uses the [raylib graphics library](https://github.com/raysan5/raylib/blob/master/src/raylib.h).

- Many tools such as include files, modules & makefiles are based on the [Lecture Code repository](https://github.com/chatziko-k08/lecture-code).
