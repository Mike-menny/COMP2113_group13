#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
using namespace std;

class Menny {
private:
    vector<vector<int>> board;
    int score;
    string level;
    bool move_single(int& current, int& next);

public:
    Menny();
    void reset();
    void save_game(const string& filename);
    bool load_game(const string& filename);
    void save_highscore();
    void show_highscores();
    void print();
    void update(string direction);
    void add_random();
    string check();
    void set_level(string new_level);
    int get_score();
    vector<vector<int>>& get_board() { return board; }
    int& get_score_ref() { return score; }
};

class BigMennyPlus {
private:
    vector<vector<int>> board;
    int score;
    string level;
    bool move_single(int& current, int& next);

public:
    BigMennyPlus();
    void reset();
    void save_game(const string& filename);
    bool load_game(const string& filename);
    void save_highscore();
    void show_highscores();
    void print();
    void update(string direction);
    void add_random();
    string check();
    void set_level(string new_level);
    int get_score();
    vector<vector<int>>& get_board() { return board; }
    int& get_score_ref() { return score; }
};

class BigMennyPro {
private:
    vector<vector<int>> board;
    int score;
    string level;
    bool move_single(int& current, int& next);

public:
    BigMennyPro();
    void reset();
    void save_game(const string& filename);
    bool load_game(const string& filename);
    void save_highscore();
    void show_highscores();
    void print();
    void update(string direction);
    void add_random();
    string check();
    void set_level(string new_level);
    int get_score();
    vector<vector<int>>& get_board() { return board; }
    int& get_score_ref() { return score; }
};

void load_game_status(std::vector<std::vector<int>>& board, int& score, std::string& level, const std::string& filename);

#endif