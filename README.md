# 2048 Game

A C++ implementation of the classic 2048 game with multiple versions and features.

## Features

- Three game versions:
  - 4x4 (Classic)
  - 5x5 (Plus)
  - 6x6 (Pro)
- Three difficulty levels:
  - Easy
  - Medium
  - Hard
- User registration and login system
- High score tracking
- Game saving and loading
- Cross-platform support (Windows/Linux)

## Prerequisites

- C++ compiler (g++ recommended)
- Make
- Windows or Linux operating system

## Compilation

1. Open a terminal in the project directory
2. Run the following command to compile the game:
```bash
make
```

## Running the Game

After compilation, run the game using:
```bash
./game
```

## Game Controls

- Use 'w', 'a', 's', 'd' keys to move tiles:
  - 'w': Move up
  - 'a': Move left
  - 's': Move down
  - 'd': Move right
- Press 'q' to quit the game
- Press 'y' when prompted to save your game progress

## Game Rules

1. Use arrow keys to move all tiles in the desired direction
2. When two tiles with the same number collide, they merge into one
3. After each move, a new tile (2 or 4) appears in a random empty cell
4. The game ends when:
   - You reach the target number (2048 in classic mode)
   - No more moves are possible

## File Structure

- `main.cpp`: Main game logic and user interface
- `library.h`/`library.cpp`: Game class definitions and implementations
- `registerUser.h`/`registerUser.cpp`: User management system
- `save.h`/`save.cpp`: Game saving functionality
- `load.h`/`load.cpp`: Game loading functionality
- `Makefile`: Compilation instructions

## Notes

- Game saves are stored in text files with the format: `username_version_save.txt`
- High scores are automatically saved after each game
- The game supports multiple user accounts with individual high scores 