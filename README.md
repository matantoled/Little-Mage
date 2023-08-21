# Author
Matan Toledano

If you have any questions or encounter any issues with this project, feel free to contact me at matantoled@gmail.com. I'll be more than happy to help!

# Little Mage
Little Mage is an original game created using the SFML graphics library. 
In this game, players control the main character, Little Mage, and navigate through three different levels. 
The goal of each level is to guide the mage to the exit door, which can be unlocked using a key. 
Players must avoid or defeat various monsters and obstacles along the way. 
The levels are time-limited, and if time runs out, the level will restart. 
Upon completing the game, players can return to the main menu to play again or exit the game.

## Gameplay Video
To see the game in action, check out the gameplay video on YouTube: [Little Mage Gameplay](https://youtu.be/Dp8TcgzrcMk)

## Getting Started
These instructions will help you get a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
This project uses the SFML graphics library. Make sure you have it installed or follow the SFML installation instructions:
https://www.sfml-dev.org/tutorials/2.6/start-linux.php

## Installing
1. Clone the repository to your local machine: `git clone <repository_url>`
2. Navigate to the project directory: `cd "Little-Mage-master/Little Mage"`
3. Create a separate build directory and navigate to it: `mkdir build && cd build`
4. Compile the project using CMake: `cmake .. && make`
5. Run the game: `./LittleMage`

## How to Play
The game consists of several levels where the objective is to guide the mage to the exit door. 
Players can move the mage using the arrow keys, jump with the "up" arrow key, and shoot with the "Left Ctrl" key. 
Players must collect keys to unlock doors and avoid or defeat enemies along the way.

## Gameplay Rules and Character Abilities

### Characters and Their Abilities
- **Little Mage (P)**: The main character controlled by the player. The mage can move left or right, jump, and shoot.
- The mage can defeat monsters by shooting at them.

### Tiles and Objects
- **Key (F)**: Collect keys to unlock doors and progress through the levels.
- **Wall (=)**: Obstacles that block the player's path.
- **Door (#)**: The exit point for each level. The mage must collect keys to unlock doors.
- **Spikes (+)**: Hazardous objects that can harm the player.
- **Fire (*)**: Hazardous objects that can harm the player.
- **Ghost (G)**: Floating enemies that move randomly across the level. The mage can defeat them by shooting at them.
- **Monster (M)**: Enemies that move along walls. The mage can defeat them by shooting at them.

## Creating Custom Levels
Levels are stored in the `resources` folder with names like `Board1.txt`, `Board2.txt`, and so on. 
To add a new level, create a text file in this folder with the name of the next level in sequence
(e.g., if there are already three levels, name the new level `Board4.txt`). 
Additionally, you need to add its name to the CMake file. In the `Little Mage/resources/CMakeLists.txt` file, 
add the following line if the new level is `Board4.txt`:

```
configure_file ("Board4.txt" ${CMAKE_BINARY_DIR} COPYONLY)
```

To properly create a level file, follow these procedures:
1. Write the number of rows and columns for the game board, followed by the time limit for the current stage. Separate these numbers with spaces and start a new line.
2. Create the game board using the character symbols listed above.

Here's an example of a custom level:

```
14 51 150
===================================================
=                             +                   =
=      +   F      G      G   ===      G           =
=      ==  ==        ===                          =
=   G           M                    #            =
=    G         ===                  ==            =
=                                                 =
=         ===       ==   ===    ==                =
=    ===         M                   G            =
=               ===                               =
===    M                                 G        =
=     ===       G                                 =
= P                                               =
====*****=====*********====************====****====
```

## Source Code Structure

### Characters
- `Player.cpp`, `Player.h`: Implementations of the player character.
- `Ghost.cpp`, `Ghost.h`: Implementations of the ghost enemy.
- `Monster.cpp`, `Monster.h`: Implementations of the monster enemy.

### Game Objects
- `Key.cpp`, `Key.h`: Implementations of the key object.
- `Wall.cpp`, `Wall.h`: Implementations of the wall object.
- `Door.cpp`, `Door.h`: Implementations of the door object.
- `Fire.cpp`, `Fire.h`: Implementations of the fire object.
- `Spikes.cpp`, `Spikes.h`: Implementations of the spikes object.

### Gameplay
- `Board.cpp`, `Board.h`: Implementations of the game board.
- `Controller.cpp`, `Controller.h`: Management of real-time events on the screen.
- `CollisionHandling.cpp`, `CollisionHandling.h`: Handling of collisions between game objects.

### User Interface
- `Toolbar.cpp`, `Toolbar.h`: Implementations of the game's toolbar.
- `Menu.cpp`, `Menu.h`: Implementations of the game's main menu.
- `Intro.cpp`, `Intro.h`: Implementations of the game's intro sequence.

### Resources
- `Resources.cpp`, `Resources.h`: Singleton design pattern for loading and accessing resources like textures and music.

## Acknowledgments
- Special thanks to my partner, Yitzhak Halevi, for his invaluable contributions to this project.
- A heartfelt thank you to Hadassah College for providing the resources and support that made this project possible.
