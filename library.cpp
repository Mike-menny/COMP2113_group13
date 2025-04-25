#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
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