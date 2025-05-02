#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/**
 * Saves the current game state (board, score, and difficulty level) to a file.
 * 
 * The function writes the game data in the following format:
 * 1. First line: difficulty level
 * 2. Second line: current score
 * 3. Subsequent lines: game board (2D matrix)
 * 
 * Inputs:
 *   - vector<vector<int>>& board: Reference to the 2D game board to be saved
 *   - int score: Current game score to save
 *   - string& level: Reference to the current difficulty level ("easy"/"medium"/"hard")
 *   - string& filename: Reference to the output filename/path
 * 
 * Outputs:
 *   - None (void function)
 *   - Creates or overwrites the specified file with game data
 *   - Prints error message to cerr if file cannot be opened
 * 
 * Error Handling:
 *   - Checks if file opened successfully
 *   - Outputs error message if file operation fails
 */
void save_game_status(vector<vector<int>>& board, int score, string& level, string& filename) {
    ofstream file(filename);
    
    if (file.is_open()) {
        // Write level and score
        file << level << std::endl;
        file << score << std::endl;
        
        // Write board state
        for (const auto& row : board) {
            for (int cell : row) {
                file << cell << " ";
            }
            file << std::endl;
        }
        
        file.close();
    } else {
        cerr << "Unable to open file for saving: " << filename << "\n";
    }
}
