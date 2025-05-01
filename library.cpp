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

// Menny class implementation
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

Menny::Menny() {
    reset();
}

void Menny::reset() {
    board = vector<vector<int>>(4, vector<int>(4, 0));
    score = 0;
    level = "easy";
}

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

void Menny::print() {
    cout << "\n";
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            cout << setw(6) << board[i][j];
        }
        cout << endl << endl;
    }
    cout << "Score: " << score << endl;
    cout<<"Level: "<<level<<endl;
    cout<< "Status: "<< check()<<endl;
}

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

void Menny::set_level(string new_level) {
    level = new_level;
}

int Menny::get_score() {
    return score;
}

// BigMennyPlus class implementation
bool BigMennyPlus::move_single(int& current, int& next) {
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

BigMennyPlus::BigMennyPlus() {
    reset();
}

void BigMennyPlus::reset() {
    board = vector<vector<int>>(5, vector<int>(5, 0));
    score = 0;
    level = "easy";
}

void BigMennyPlus::save_game(const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error saving game!" << endl;
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
    
    cout << "Game saved to " << filename << endl;
}

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

void BigMennyPlus::show_highscores() {
    ifstream infile("highscores.txt");
    if (!infile) {
        cout << "No highscores recorded yet." << endl;
        return;
    }

    cout << "\n===== HIGHSCORES =====" << endl;
    string lvl;
    int scr;
    while (infile >> lvl >> scr) {
        cout << lvl << ": " << scr << endl;
    }
    cout << "=====================" << endl;
}

void BigMennyPlus::print() {
    cout << "\n";
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            cout << setw(6) << board[i][j];
        }
        cout << endl << endl;
    }
    cout << "Score: " << score << endl;
    cout << "Level: " << level << endl;
    cout << "Status: " << check() << endl;
}

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

void BigMennyPlus::set_level(string new_level) {
    level = new_level;
}

int BigMennyPlus::get_score() {
    return score;
}

// BigMennyPro class implementation
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

BigMennyPro::BigMennyPro() {
    reset();
}

void BigMennyPro::reset() {
    board = vector<vector<int>>(6, vector<int>(6, 0));
    score = 0;
    level = "easy";
}

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

void BigMennyPro::print() {
    cout << "\n";
    for(int i = 0; i < 6; ++i) {  
        for(int j = 0; j < 6; ++j) {
            cout << setw(6) << board[i][j];
        }
        cout << endl << endl;
    }
    cout << "Score: " << score << endl;
    cout << "Level: " << level << endl;
    cout << "Status: " << check() << endl;
}

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

void BigMennyPro::set_level(string new_level) {
    level = new_level;
}

int BigMennyPro::get_score() {
    return score;
}


