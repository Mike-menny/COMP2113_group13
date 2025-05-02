#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>
#include <sstream>
#include "registerUser.h"
#include "library.h"
using namespace std;


/**
 * Movement rules:
 * 1. If next tile is empty (0), move current tile there
 * 2. If tiles have same value, merge them (double next tile's value)
 */
bool Menny::move_single(int& current, int& next) {
    if (next == 0) {
        next = current;
        current = 0;
        return true;
    } else if (current == next) {
        next *= 2;
        score += next;
        current = 0;
        return true;
    }
    return false;
}

/**
 * @brief Constructor - Initializes game state
 */
Menny::Menny() {
    reset();
}

/**
 * @brief Resets the game to initial state
 * 
 * Creates 4x4 game board (all zeros)
 * Resets score to 0
 * Sets default difficulty to "easy"
 */
void Menny::reset() {
    board = vector<vector<int>>(4, vector<int>(4, 0));
    score = 0;
    level = "easy";
}

/**
 * @brief Saves current game state to file
 * @param filename Name of file to save to
 * 
 * File format:
 * Line 1: Current difficulty level
 * Line 2: Current score
 * Next 4 lines: Board state (space-separated values)
 */
void Menny::save_game(const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error saving 4x4 game!" << endl;
        return;
    }

    outfile << level << endl;
    outfile << score << endl;
    
    for (const auto& row : board) {
        for (int val : row) {
            outfile << val << " ";
        }
        outfile << endl;
    }
    
    cout << "4x4 Game saved to " << filename << endl;
}

/**
 * @brief Loads game state from file
 * @param filename Name of file to load from
 * @return bool True if load successful, false otherwise
 */
bool Menny::load_game(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error loading 4x4 game!" << endl;
        return false;
    }

    string line;
    getline(infile, line);
    level = line;
    
    getline(infile, line);
    score = stoi(line);
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            infile >> board[i][j];
        }
    }
    
    cout << "4x4 Game loaded from " << filename << endl;
    return true;
}

/**
 * @brief Saves high score to file
 * 
 * Reads existing highscores from highscores_4x4.txt
 * Updates record if current score is higher
 * File format: Each line "level score"
 */
void Menny::save_highscore() {
    map<string, int> highscores;
    
    ifstream infile("highscores_4x4.txt"); 
    if (infile) {
        string lvl;
        int scr;
        while (infile >> lvl >> scr) {
            highscores[lvl] = scr;
        }
        infile.close();
    }

    if (score > highscores[level]) {
        highscores[level] = score;

        ofstream outfile("highscores_4x4.txt");
        for (const auto& entry : highscores) {
            outfile << entry.first << " " << entry.second << endl;
        }
        cout << "New 4x4 highscore for " << level << ": " << score << endl;
    }
}

/**
 * @brief Displays all high scores
 * 
 * Reads from highscores_4x4.txt and formats output
 * Shows "No highscores" message if file doesn't exist
 */
void Menny::show_highscores() {
    ifstream infile("highscores_4x4.txt");
    if (!infile) {
        cout << "No 4x4 highscores yet." << endl;
        return;
    }

    cout << "\n===== 4x4 HIGHSCORES =====" << endl;
    string lvl;
    int scr;
    while (infile >> lvl >> scr) {
        cout << lvl << ": " << scr << endl;
    }
    cout << "=========================" << endl;
}

/**
 * @brief Prints current game state
 * 
 * Output includes:
 * 1. Color-formatted 4x4 game board (0 shown as .)
 * 2. Current score
 * 3. Current difficulty level
 * 4. Game status from check()
 * 
 * Color scheme:
 * 2/4: Red | 8/16: Yellow | 32/64: Green
 * 128/256: Cyan | 512/1024: Blue | 2048/4096: Magenta
 */
void Menny::print() {
    cout << "\n";
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(board[i][j] == 0) {
                cout << setw(6) << ".";
            } else if(board[i][j] == 2 || board[i][j] == 4) {
                cout << "\033[31m" << setw(6) << board[i][j] << "\033[0m";
            } else if(board[i][j] == 8 || board[i][j] == 16) {
                cout << "\033[33m" <<setw(6) << board[i][j] << "\033[0m";
            } else if(board[i][j] == 32 || board[i][j] == 64) {
                cout <<  "\033[32m" << setw(6) <<board[i][j] << "\033[0m";
            } else if(board[i][j] == 128 || board[i][j] == 256) {
                cout <<  "\033[36m" << setw(6) <<board[i][j] << "\033[0m";
            } else if(board[i][j] == 512 || board[i][j] == 1024) {
                cout <<  "\033[34m" <<setw(6) << board[i][j] << "\033[0m";
            } else if(board[i][j] == 2048 || board[i][j] == 4096) {
                cout <<  "\033[35m" <<setw(6) << board[i][j] << "\033[0m";
            }
        }
        cout << endl << endl;
    }
    cout << "Score: " << score << endl;
    cout<<"Level: "<<level<<endl;
    cout<< "Status: "<< check()<<endl;
}

/**
 * @brief Processes player movement
 * @param direction Movement direction (w/a/s/d for up/left/down/right)
 * 
 * Movement logic:
 * 1. Iterates through all tiles
 * 2. For each non-zero tile, attempts movement in specified direction
 * 3. Uses move_single() for actual movement/merging
 */
void Menny::update(string direction) {
    if(direction == "w") {
        for(int j = 0; j < 4; ++j) {
            for(int i = 1; i < 4; ++i) {
                if(board[i][j] == 0) continue;
                int k = i;
                while(k > 0 && move_single(board[k][j], board[k-1][j])) {
                    k--;
                }
            }
        }
    } else if(direction == "s") {
        for(int j = 0; j < 4; ++j) {
            for(int i = 2; i >= 0; --i) {
                if(board[i][j] == 0) continue;
                int k = i;
                while(k < 3 && move_single(board[k][j], board[k+1][j])) {
                    k++;
                }
            }
        }
    } else if(direction == "a") {
        for(int i = 0; i < 4; ++i) {
            for(int j = 1; j < 4; ++j) {
                if(board[i][j] == 0) continue;
                int k = j;
                while(k > 0 && move_single(board[i][k], board[i][k-1])) {
                    k--;
                }
            }
        }
    } else if(direction == "d") {
        for(int i = 0; i < 4; ++i) {
            for(int j = 2; j >= 0; --j) {
                if(board[i][j] == 0) continue;
                int k = j;
                while(k < 3 && move_single(board[i][k], board[i][k+1])) {
                    k++;
                }
            }
        }
    }
}

/**
 * @brief Adds random tile to empty position
 * 
 * Tile generation probabilities by difficulty:
 * - easy: 80% chance of 2
 * - medium: 60% chance of 2
 * - hard: 40% chance of 2
 * Does nothing if no empty positions available
 */
void Menny::add_random() {
    vector<pair<int, int>> empty_cells;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(board[i][j] == 0) {
                empty_cells.push_back({i, j});
            }
        }
    }
    
    if(empty_cells.empty()) {return;}
    
    srand(time(NULL));
    int index = rand() % empty_cells.size();
    int value;
    if(level=="easy"){ 
        srand(time(NULL));
        value = (rand() % 10 < 8) ? 2 : 4;
    }else if(level=="medium"){
        srand(time(NULL));
        value = (rand() % 10 < 6) ? 2 : 4;
    }else if(level=="hard"){
        srand(time(NULL));
        value = (rand() % 10 < 4) ? 2 : 4;
    }
    board[empty_cells[index].first][empty_cells[index].second] = value;
}

/**
 * @brief Checks current game state
 * @return string Game status message
 * 
 * Possible return values:
 * - "You've reached 2048! nb" when any tile reaches 2048
 * - "playing" when empty tiles or possible merges exist
 * - "wrong move" when board is full but merges are possible
 * - "lose" when game over (no moves possible)
 */
string Menny::check() {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(board[i][j] == 2048) {
                return "You've reached 2048! nb";
            }
        }
    }

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(board[i][j] == 0) {
                return "playing";
            }
        }
    }

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(j < 3 && board[i][j] == board[i][j+1]) {
                return "wrong move";
            }
            if(i < 3 && board[i][j] == board[i+1][j]) {
                return "wrong move";
            }
        }
    }

    return "lose";
}

/**
 * @brief Loads game state from a file
 * @param filename The name of the file to load from
 * @return bool True if loading succeeded, false otherwise
 * 
 * File format expected:
 * Line 1: Difficulty level
 * Line 2: Current score
 * Next 5 lines: 5x5 game board (space-separated values)
 */
bool BigMennyPlus::load_game(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error loading game!" << endl;
        return false;
    }

    string line;
    getline(infile, line);
    level = line;
    
    getline(infile, line);
    score = stoi(line);
    
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            infile >> board[i][j];
        }
    }
    
    cout << "Game loaded from " << filename << endl;
    return true;
}

/**
 * @brief Saves current score as high score if applicable
 * 
 * Reads existing highscores from "highscores.txt"
 * Updates record if current score is higher than stored value for current level
 * File format: Each line contains "level score"
 */
void BigMennyPlus::save_highscore() {
    map<string, int> highscores;
    
    ifstream infile("highscores.txt");
    if (infile) {
        string lvl;
        int scr;
        while (infile >> lvl >> scr) {
            highscores[lvl] = scr;
        }
        infile.close();
    }

    if (score > highscores[level]) {
        highscores[level] = score;

        ofstream outfile("highscores.txt");
        for (const auto& entry : highscores) {
            outfile << entry.first << " " << entry.second << endl;
        }
        cout << "New highscore for " << level << ": " << score << endl;
    }
}

/**
 * @brief Displays all recorded high scores
 * 
 * Reads from "highscores.txt" and formats the output
 * Shows "No highscores" message if file doesn't exist
 */

// Applies a move to the board in the specified direction ("w", "a", "s", "d").
// Inputs:
// - direction: a string representing the movement direction
//              "w" = up, "s" = down, "a" = left, "d" = right
// Outputs:
// - Modifies the board by shifting and merging tiles based on game rules.
void BigMennyPlus::update(string direction) {
    if(direction == "w") {
        for(int j = 0; j < 5; ++j) {
            for(int i = 1; i < 5; ++i) {
                if(board[i][j] == 0) continue;
                int k = i;
                while(k > 0 && move_single(board[k][j], board[k-1][j])) {
                    k--;
                }
            }
        }
    } else if(direction == "s") {
        for(int j = 0; j < 5; ++j) {
            for(int i = 3; i >= 0; --i) {
                if(board[i][j] == 0) continue;
                int k = i;
                while(k < 4 && move_single(board[k][j], board[k+1][j])) {
                    k++;
                }
            }
        }
    } else if(direction == "a") {
        for(int i = 0; i < 5; ++i) {
            for(int j = 1; j < 5; ++j) {
                if(board[i][j] == 0) continue;
                int k = j;
                while(k > 0 && move_single(board[i][k], board[i][k-1])) {
                    k--;
                }
            }
        }
    } else if(direction == "d") {
        for(int i = 0; i < 5; ++i) {
            for(int j = 3; j >= 0; --j) {
                if(board[i][j] == 0) continue;
                int k = j;
                while(k < 4 && move_single(board[i][k], board[i][k+1])) {
                    k++;
                }
            }
        }
    }
}

// Adds a new random tile (2, 4, or 8) to an empty cell on the board.
// Inputs:
// - None (uses current board and level state)
// Outputs:
// - Updates the board by inserting a new value at a random empty position
void BigMennyPlus::add_random() {
    vector<pair<int, int>> empty_cells;
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            if(board[i][j] == 0) {
                empty_cells.push_back({i, j});
            }
        }
    }
    
    if(empty_cells.empty()) { return; }

    srand(time(NULL));
    int index = rand() % empty_cells.size();

    int value;
    int random_num = rand() % 10;

    if(level == "easy") {
        if(random_num < 8) value = 2;
        else if(random_num < 9) value = 4;
        else value = 8;
    }
    else if(level == "medium") {
        if(random_num < 6) value = 2;
        else if(random_num < 8) value = 4;
        else value = 8;
    }
    else if(level == "hard") {
        if(random_num < 4) value = 2;
        else if(random_num < 7) value = 4;
        else value = 8;
    }

    board[empty_cells[index].first][empty_cells[index].second] = value;
}

// Checks the current game status: win, ongoing, or lose.
// Inputs:
// - None (uses current board state)
// Outputs:
// - Returns a string indicating game status:
//     "You've reached 4096!" if win,
//     "playing" if moves are still possible,
//     "lose" if no moves remain.
string BigMennyPlus::check() {
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            if(board[i][j] == 4096) {
                return "You've reached 4096!";
            }
        }
    }

    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            if(board[i][j] == 0) {
                return "playing";
            }
        }
    }

    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            if(j < 4 && board[i][j] == board[i][j+1]) {
                return "playing";
            }
            if(i < 4 && board[i][j] == board[i+1][j]) {
                return "playing";
            }
        }
    }

    return "lose";
}

// Sets the difficulty level of the game.
// Inputs:
// - new_level: string representing the difficulty ("easy", "medium", "hard")
// Outputs:
// - Updates the internal level state
void BigMennyPlus::set_level(string new_level) {
    level = new_level;
}

// Returns the current game score.
// Inputs: None
// Outputs: Integer value of the current score.
int BigMennyPlus::get_score() {
    return score;
}

// BigMennyPro class implementation
// Moves a single tile in the board.
// Inputs: 'current' and 'next' are references to adjacent cells in the direction of movement.
// Outputs: Returns true if a move or merge occurred, and updates 'score' if tiles merged
bool BigMennyPro::move_single(int& current, int& next) {   
    if (next == 0) {
        next = current;
        current = 0;
        return true;
    } else if (current == next) {
        next *= 2;
        score += next;
        current = 0;
        return true;
    }
    return false;
}

// Constructor for BigMennyPro class.
// Initializes the game state by calling the reset function.
BigMennyPro::BigMennyPro() {    
    reset();
}

// Resets the board to an empty 6x6 grid and sets the initial score and difficulty level.
// Inputs: None.
// Outputs: Modifies internal state.
void BigMennyPro::reset() {
    board = vector<vector<int>>(6, vector<int>(6, 0));
    score = 0;
    level = "easy";
}

// Saves the current game state to a file.
// Inputs: 'filename' - the name of the file to save the game state to.
// Outputs: Writes level, score, and board values to file.
void BigMennyPro::save_game(const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error saving 6x6 game!" << endl;
        return;
    }

    outfile << level << endl;
    outfile << score << endl;
    
    for (const auto& row : board) {
        for (int val : row) {
            outfile << val << " ";
        }
        outfile << endl;
    }
    
    cout << "6x6 Game saved to " << filename << endl;
}

// Loads a previously saved game state from a file.
// Inputs: 'filename' - the name of the file to load the game state from.
// Outputs: Updates board, score, and level; returns true if successful, false
bool BigMennyPro::load_game(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error loading 6x6 game!" << endl;
        return false;
    }

    string line;
    getline(infile, line);
    level = line;
    
    getline(infile, line);
    score = stoi(line);
    
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            infile >> board[i][j];
        }
    }
    
    cout << "6x6 Game loaded from " << filename << endl;
    return true;
}

// Saves the current score as a high score if it exceeds the existing value for the level.
// Inputs: None.
// Outputs: Updates the highscore file if necessary
void BigMennyPro::save_highscore() {
    map<string, int> highscores;
    
    ifstream infile("highscores_6x6.txt");
    if (infile) {
        string lvl;
        int scr;
        while (infile >> lvl >> scr) {
            highscores[lvl] = scr;
        }
        infile.close();
    }

    if (score > highscores[level]) {
        highscores[level] = score;

        ofstream outfile("highscores_6x6.txt");
        for (const auto& entry : highscores) {
            outfile << entry.first << " " << entry.second << endl;
        }
        cout << "New 6x6 highscore for " << level << ": " << score << endl;
    }
}

// Displays the high scores for all levels.
// Inputs: None.
// Outputs: Prints high scores to the console.
void BigMennyPro::show_highscores() {
    ifstream infile("highscores_6x6.txt");
    if (!infile) {
        cout << "No 6x6 highscores yet." << endl;
        return;
    }

    cout << "\n===== 6x6 HIGHSCORES =====" << endl;
    string lvl;
    int scr;
    while (infile >> lvl >> scr) {
        cout << lvl << ": " << scr << endl;
    }
    cout << "=========================" << endl;
}

// Prints the current board state to the console with colored tiles and score information.
// Inputs: None.
// Outputs: Console output of the board, score, level, and current status.
void BigMennyPro::print() {
    cout << "\n";
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 6; ++j) {
            if(board[i][j] == 0) {
                cout << setw(6) << ".";
            } else if(board[i][j] == 2 || board[i][j] == 4) {
                cout << "\033[31m" << setw(6) << board[i][j] << "\033[0m";
            } else if(board[i][j] == 8 || board[i][j] == 16) {
                cout << "\033[33m" <<setw(6) << board[i][j] << "\033[0m";
            } else if(board[i][j] == 32 || board[i][j] == 64) {
                cout <<  "\033[32m" << setw(6) <<board[i][j] << "\033[0m";
            } else if(board[i][j] == 128 || board[i][j] == 256) {
                cout <<  "\033[36m" << setw(6) <<board[i][j] << "\033[0m";
            } else if(board[i][j] == 512 || board[i][j] == 1024) {
                cout <<  "\033[34m" <<setw(6) << board[i][j] << "\033[0m";
            } else if(board[i][j] == 2048 || board[i][j] == 4096) {
                cout <<  "\033[35m" <<setw(6) << board[i][j] << "\033[0m";
            }
        }
        cout << endl << endl;
    }
    cout << "Score: " << score << endl;
    cout << "Level: " << level << endl;
    cout << "Status: " << check() << endl;
}

// Applies a move based on the user's direction input ("w", "a", "s", or "d").
// Inputs: 'direction' string representing the movement direction.
// Outputs: Modifies the board state through tile shifting and merging.
void BigMennyPro::update(string direction) {
    if(direction == "w") {  
        for(int j = 0; j < 6; ++j) {  
            for(int i = 1; i < 6; ++i) {
                if(board[i][j] == 0) continue;
                int k = i;
                while(k > 0 && move_single(board[k][j], board[k-1][j])) {
                    k--;
                }
            }
        }
    } else if(direction == "s") {  
        for(int j = 0; j < 6; ++j) {  
            for(int i = 4; i >= 0; --i) {
                if(board[i][j] == 0) continue;
                int k = i;
                while(k < 5 && move_single(board[k][j], board[k+1][j])) {
                    k++;
                }
            }
        }
    } else if(direction == "a") {  
        for(int i = 0; i < 6; ++i) {  
            for(int j = 1; j < 6; ++j) {
                if(board[i][j] == 0) continue;
                int k = j;
                while(k > 0 && move_single(board[i][k], board[i][k-1])) {
                    k--;
                }
            }
        }
    } else if(direction == "d") {  
        for(int i = 0; i < 6; ++i) {  
            for(int j = 4; j >= 0; --j) {
                if(board[i][j] == 0) continue;
                int k = j;
                while(k < 5 && move_single(board[i][k], board[i][k+1])) {
                    k++;
                }
            }
        }
    }
}

// Adds a random tile (2, 4, or 8) to an empty cell on the board, based on the difficulty level.
// Inputs: None.
// Outputs: Updates the board by inserting a new tile.
void BigMennyPro::add_random() {
    vector<pair<int, int>> empty_cells;
    for(int i = 0; i < 6; ++i) {  
        for(int j = 0; j < 6; ++j) {
            if(board[i][j] == 0) {
                empty_cells.push_back({i, j});
            }
        }
    }

    if(empty_cells.empty()) { return; }

    srand(time(NULL));
    int index = rand() % empty_cells.size();

    int value;
    int random_num = rand() % 10;

    if(level == "easy") {
        if(random_num < 8) value = 2;
        else if(random_num < 9) value = 4;
        else value = 8;
    }
    else if(level == "medium") {
        if(random_num < 6) value = 2;
        else if(random_num < 8) value = 4;
        else value = 8;
    }
    else if(level == "hard") {
        if(random_num < 4) value = 2;
        else if(random_num < 7) value = 4;
        else value = 8;
    }

    board[empty_cells[index].first][empty_cells[index].second] = value;
}

// Evaluates and returns the current game status.
// Inputs: None.
// Outputs: Returns a string - "playing", "lose", or "You've reached 4096!".
string BigMennyPro::check() {
    for(int i = 0; i < 6; ++i) {  
        for(int j = 0; j < 6; ++j) {
            if(board[i][j] == 4096) {
                return "You've reached 4096!";
            }
        }
    }

    for(int i = 0; i < 6; ++i) {  
        for(int j = 0; j < 6; ++j) {
            if(board[i][j] == 0) {
                return "playing";
            }
        }
    }

    for(int i = 0; i < 6; ++i) {  
        for(int j = 0; j < 6; ++j) {
            if(j < 5 && board[i][j] == board[i][j+1]) {
                return "playing";
            }
            if(i < 5 && board[i][j] == board[i+1][j]) {
                return "playing";
            }
        }
    }

    return "lose";
}

// Sets the difficulty level of the game.
// Inputs: 'new_level' - a string representing the difficulty ("easy", "medium", "hard").
// Outputs: Modifies the internal level setting.
void BigMennyPro::set_level(string new_level) {
    level = new_level;
}

// Returns the current score of the player.
// Inputs: None.
// Outputs: Integer score value.
int BigMennyPro::get_score() {
    return score;
}
