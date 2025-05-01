#include <fstream>
#include <iostream>
#include <vector>
#include <string>

/**
 *The load_game_status function loads a saved game state from a specified file.
 *@param board the 2D vector representing the game board (passed by reference and modified)
 *@param score the variable to store the loaded game score (passed by reference)
 *@param level the string to store the loaded game level (passed by reference)
 *@param filename the name/path of the file from which to load the game data
 *@return none, but modifies the board, score, and level parameters with loaded values
 */

void load_game_status(vector<vector<int>>& board, int& score, string& level, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> level;
        file >> score;
        for (auto& row : board) {
            for (int& cell : row) {
                file >> cell;
            }
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for loading." << endl;
    }
}
