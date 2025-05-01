#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
/**
*The save_game_status function saves the current game board, score, and level to a specified file.
*@param board the 2D vector representing the game board
*@param score the current game score to be saved
*@param level the current game level/difficulty to be saved
*@param filename the name/path of the file where data will be saved
*@return none, but creates/overwrites a file with the game data
*/
void save_game_status(vector<vector<int>>& board, int score, string& level, string& filename){
  ofstream file(filename);
  if(file.is_open()){
    file << level << std::endl;
        file << score << std::endl;
        for (const auto& row : board) {
            for (int cell : row) {
                file << cell << " ";
            }
            file << std::endl;
        }
        file.close();
  } else {
    cerr<<"Unable to open file!\n";
  }
}
