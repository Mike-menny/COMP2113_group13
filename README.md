# 2048 Game

A C++ implementation of the classic 2048 game with multiple board sizes and difficulty levels.

## Features

- Three game modes:
  - 4x4 (Classic)
  - 5x5 (Plus)
  - 6x6 (Pro)
- Three difficulty levels:
  - Easy
  - Medium
  - Hard
- User account system:
  - Registration
  - Login
  - Score tracking
  - Game saving and loading
- Colorful console interface
- High score tracking for each game mode

## Requirements

- C++11 or later
- GCC/G++ compiler
- Standard C++ libraries
- Filesystem library (stdc++fs)

## Compilation

To compile the game, simply run:

```bash
make
```

This will create an executable named `game`.

## How to Play

1. Run the game:
   ```bash
   ./game
   ```

2. Choose to register a new account or login with an existing one.

3. Select your preferred game mode (4x4, 5x5, or 6x6).

4. Choose the difficulty level (Easy, Medium, or Hard).

5. Use the following controls:
   - `w`: Move up
   - `a`: Move left
   - `s`: Move down
   - `d`: Move right
   - `q`: Quit game

6. The game ends when:
   - You reach the target number (2048 for 4x4, 4096 for 5x5 and 6x6)
   - No more moves are possible

## Game Rules

1. Tiles with the same number merge into one when they collide.
2. After each move, a new tile (2, 4, or 8) appears in a random empty cell.
3. The probability of higher numbers appearing increases with difficulty level.
4. Your score increases by the value of merged tiles.

## File Structure

- `main.cpp`: Main game logic and user interface
- `registerUser.h`: User account management declarations
- `registerUser.cpp`: User account management implementation
- `library.h`: Game class declarations
- `library.cpp`: Game class implementations
- `Makefile`: Build configuration

## User Data

User data is stored in text files with the following format:
```
username
highestScore4
highestScore5
highestScore6
```

Game saves are stored in separate files with the format:
```
username_4x4_save.txt
username_5x5_save.txt
username_6x6_save.txt
```

## Development Team

- Group 13
- COMP2113 Project

## License

This project is licensed under the MIT License - see the LICENSE file for details. 