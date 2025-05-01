#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
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
