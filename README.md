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
- Miao Yuyang 3036264303
- Ma Xinyi 3036128767
- Ying Zichuan 3036265113
- Ni Feiyang 3036272908
- Lyu Qingyang 3036127074

## License

This project is licensed under the MIT License - see the LICENSE file for details. 

## List of Features
1. **Grid-Based Game Board**
   - 4x4 (Menny), 5x5 (BigMennyPlus), and 6x6 (BigMennyPro) variants
   - Dynamic initialization with `vector<vector<int>>`

2. **Tile Movement System**
   - Directional controls (`w/a/s/d` for up/left/down/right)
   - Tile merging logic (doubling value on collision)
   - Score accumulation during merges

3. **Random Tile Generation**
   - Difficulty-based probabilities:
     - Easy: 4*4 board
     - Medium: 5*5 board  
     - Hard: 6*6 board
   - Empty cell detection before placement

4. **Win/Lose Conditions**
   - Win: Reach 2048 (4x4/5x5) or 4096 (6x6)
   - Lose: No valid moves remaining (board full + no merges possible)
   - Intermediate states: "playing", "wrong move"
     
5. **Game State Saving/Loading**
   - File format:
     - Line 1: Difficulty level
     - Line 2: Current score
     - Subsequent lines: Board state (space-separated values)
   - Error handling for file operations

6. **Highscore System**
   - Per-difficulty tracking (easy/medium/hard)
   - File storage (`highscores_[size].txt`)
   - Auto-update when new record achieved
   - Display formatted highscores table
     
7. **Color-Coded Board Display**
   - ANSI color schemes by tile value:
     - 2/4: Red | 8/16: Yellow | 32/64: Green
     - 128/256: Cyan | 512/1024: Blue | 2048+/4096: Magenta
   - Zero tiles shown as `.` with uniform spacing

8. **Real-Time Status Updates**
   - Current score display
   - Active difficulty level
   - Game state ("playing"/"lose"/win message)

9. **Difficulty Settings**
   - Affects:
     - Random tile spawn probabilities
     - Highscore tracking (separate records per level)
   - Configurable via `set_level()`

10. **Polymorphic Design**
    - Three game modes sharing core logic:
      - `Menny` (4x4 classic)
      - `BigMennyPlus` (5x5 extended)
      - `BigMennyPro` (6x6 challenge)
    - Consistent API across modes (`move_single()`, `add_random()`, etc.)

11. **Input Validation**
    - Directional move verification
    - File existence checks for save/load
    - Empty cell validation before tile generation
      
12. **Efficient Board Processing**
    - Nested loops with early termination (`continue` on empty tiles)
    - Direction-specific traversal logic (e.g., reverse iteration for down/right moves)

13. **Seed Management**
    - `srand(time(NULL))` for randomized tile spawning

14. **Modular Documentation**
    - Doxygen-style comments for all methods
    - Clear separation of public/private members

