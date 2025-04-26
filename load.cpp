#include <fstream>
#include <iostream>
#include <vector>
#include <string>

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
