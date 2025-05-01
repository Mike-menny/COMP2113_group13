#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

class Menny {     //Menny is a class that store the current board, score, and level info
private:
    vector<vector<int>> board;
    int score;
    string level;

    //move a single block by exchanging values
    bool move_single(int& current, int& next) {
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

public:
    Menny() {
        reset();
    }

    void reset() {
        board = vector<vector<int>>(4, vector<int>(4, 0));
        score = 0;
        level = "easy";
    }

    void print() {
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

    void update(string direction) {
        bool moved = false;
        
        if(direction == "w") {
            for(int j = 0; j < 4; ++j) {
                for(int i = 1; i < 4; ++i) {
                    if(board[i][j] == 0) continue;
                    int k = i;
                    while(k > 0 && move_single(board[k][j], board[k-1][j])) {
                        moved = true;
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
                        moved = true;
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
                        moved = true;
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
                        moved = true;
                        k++;
                    }
                }
            }
        }
    }

    void add_random() {
        ///add 2 or 4 to a random empty box
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

    string check() {
        // Check for win condition
        for(int i = 0; i < 4; ++i) {
            for(int j = 0; j < 4; ++j) {
                if(board[i][j] == 2048) {
                    return "You've reached 2048! nb";
                }
            }
        }

        // Check for empty cells
        for(int i = 0; i < 4; ++i) {
            for(int j = 0; j < 4; ++j) {
                if(board[i][j] == 0) {
                    return "playing";
                }
            }
        }

        // Check for possible merges in all directions
        for(int i = 0; i < 4; ++i) {
            for(int j = 0; j < 4; ++j) {
                // Check right
                if(j < 3 && board[i][j] == board[i][j+1]) {
                    return "wrong move";
                }
                // Check down
                if(i < 3 && board[i][j] == board[i+1][j]) {
                    return "wrong move";
                }
            }
        }

        return "lose";
    }

    void set_level(string new_level) {
        level = new_level;
    }

    int get_score() {
        return score;
    }
};

//5*5 Version
class BigMennyPlus {
private:
    vector<vector<int>> board;
    int score;
    string level;

    bool move_single(int& current, int& next) {
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

public:
    BigMennyPlus() {
        reset();
    }

    void reset() {
        board = vector<vector<int>>(5, vector<int>(5, 0));
        score = 0;
        level = "easy";
    }

    // Start of File I/O 
    void save_game(const string& filename) {
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

    bool load_game(const string& filename) {
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

    void save_highscore() {
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

        if (score > highscores[level]) {       // update
            highscores[level] = score;

            ofstream outfile("highscores.txt");       // read back
            for (const auto& entry : highscores) {
                outfile << entry.first << " " << entry.second << endl;
            }
            cout << "New highscore for " << level << ": " << score << endl;
        }
    }

    void show_highscores() {
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
    // end of File I/O 

    void print() {
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

    void update(string direction) {
        bool moved = false;
        
        if(direction == "w") {  
            for(int j = 0; j < 5; ++j) {
                for(int i = 1; i < 5; ++i) {
                    if(board[i][j] == 0) continue;
                    int k = i;
                    while(k > 0 && move_single(board[k][j], board[k-1][j])) {
                        moved = true;
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
                        moved = true;
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
                        moved = true;
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
                        moved = true;
                        k++;
                    }
                }
            }
        }
    }

    void add_random() {
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

    string check() {
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

    void set_level(string new_level) {
        level = new_level;
    }

    int get_score() {
        return score;
    }
};

//6*6 Version
class BigMennyPro {    //BigMenny Pro is a class that stores the current board state, score, and level information 
private:
    vector<vector<int>> board;
    int score;
    string level;

    bool move_single(int& current, int& next) {   
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
// move a single number in the board and change values
// Inputs: current (reference to the current cell), next (reference to the target cell)
// Outputs: true if a move or merge occurred; false otherwise

public:
    BigMennyPro() {  //initializes a new game board
        reset();
    }

    void reset() {  // resets the game to its initial state
        board = vector<vector<int>>(6, vector<int>(6, 0));  // change the board to 6*6
        score = 0;
        level = "easy";
    }

    void print() {    // print the 6*6 board, current score, level and stauts
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

    void update(string direction) {   // Update the board according to the given move direction(w/a/s/d)
        bool moved = false;

        if(direction == "w") {  
            for(int j = 0; j < 6; ++j) {  
                for(int i = 1; i < 6; ++i) {
                    if(board[i][j] == 0) continue;
                    int k = i;
                    while(k > 0 && move_single(board[k][j], board[k-1][j])) {
                        moved = true;
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
                        moved = true;
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
                        moved = true;
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
                        moved = true;
                        k++;
                    }
                }
            }
        }
    }

    void add_random() {  // Add a random new number (2, 4, or 8) to an empty box
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

    string check() {    // check the current status: win/playing/lose
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

    void set_level(string new_level) {  // sets the current game difficulty level
        level = new_level;
    }

    int get_score() {  //returns the current score
        return score;
    }
};


int main() {
    string direction;
    Menny game;
    game.reset();
    game.set_level("hard");
    game.add_random();
    game.add_random();
    game.print();
    
    while(true) {
        cin >> direction;
        if(direction == "q") break;
        game.update(direction);
        game.print();
        game.add_random();
        game.print();
        
        string status = game.check();
        if(status == "win") {
            cout << "Congratulations! You won!" << endl;
            break;
        } else if(status == "lose") {
            cout << "Game Over!" << endl;
            break;
        }
    }
    return 0;
}
