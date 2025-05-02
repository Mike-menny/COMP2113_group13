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
#include "save.h"
#include "load.h"
#include "library.h"
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;
using namespace std;

/**
 * Clears the console screen in a cross-platform manner
 * - Windows: Uses WinAPI console functions
 * - Other platforms: Uses ANSI escape codes
 * Input: None
 * Output: None (clears the screen visually)
 */

void clearScreen() {
    #if defined(_WIN32)
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord = {0, 0};
        DWORD count;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hStdOut, &csbi);
        FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        SetConsoleCursorPosition(hStdOut, coord);
    #else
        std::cout << "\033[2J\033[1;1H";
    #endif
}


/**
 * Main game application entry point
 * Handles:
 * - User registration/login
 * - Game version selection
 * - Difficulty setting
 * - Game initialization and main loop
 * - Save/load functionality
 * Input: None (command line execution)
 * Output: Returns 0 on successful program exit
 */

int main() {
    account user;  // Stores current user's game data
    
    // User authentication system
    while(true) {
        cout << "1. Register\n2. Login\n3. Exit\nChoose: ";
        string choice;
        getline(cin, choice);

        // Input validation
        while(choice != "1" && choice != "2" && choice != "3"){
            cout << "Invalid choice! Please enter again (1-3): ";
            getline(cin, choice);
        }
        
        if(choice == "1") {
            // User registration
            user = registerUser();  // Calls registration function
            cout << "Registered successfully!\n";
            break;
        } 
        else if(choice == "2") {
            // User login
            cout << "Enter username: ";
            string username;
            getline(cin, username);

            // Verify username exists
            while(!checkuser(username)){ 
                cout<<"username not found. plz enter again:";
                getline(cin, username);
            }

            // Load user data
            readuser(username+".txt", user); 

             // Display user's high scores
            cout << "\nYour highest scores:\n";
            cout << "4x4: " << user.highestScore4 << endl;
            cout << "5x5: " << user.highestScore5 << endl;
            cout << "6x6: " << user.highestScore6 << endl;
            break;
        }
        else if(choice == "3") {
            return 0;
        }
    }

     // Game version selection menu
    string gameChoice;
    cout << "\nSelect Game Version:\n"
         << "1. 4x4 (Classic)\n"
         << "2. 5x5 (Plus)\n"
         << "3. 6x6 (Pro)\n"
         << "Choice: ";
    getline(cin, gameChoice);

     // Validate game choice input
    while(gameChoice != "1" && gameChoice != "2" && gameChoice != "3"){
        cout << "Invalid choice! Please enter again (1-3): ";
        getline(cin, gameChoice);
    }

     // Difficulty level selection
    string level;
    cout << "\nSelect Difficulty:\n"
         << "1. Easy\n"
         << "2. Medium\n"
         << "3. Hard\n"
         << "Choice: ";
    string levelChoice;
    getline(cin, levelChoice);

    // Validate difficulty input
    while(levelChoice != "1" && levelChoice != "2" && levelChoice != "3"){
        cout << "Invalid choice! Please enter again (1-3): ";
        getline(cin, levelChoice);
    }

     // Set difficulty string
    if(levelChoice == "1") level = "easy";
    else if(levelChoice == "2") level = "medium";
    else level = "hard";

   // Game object pointers
    Menny* game4x4 = nullptr;
    BigMennyPlus* game5x5 = nullptr;
    BigMennyPro* game6x6 = nullptr;
    
    string direction;
    cout << "plz input wasd:";
    bool gameRunning = true; // Main game loop control flag


    // 4x4 Game Version
    if(gameChoice == "1") {
        game4x4 = new Menny();  // Initialize 4x4 game
        bool loadedSave = false; // Flag for save file detection

        // Check for existing save file
        for (const auto& entry : fs::directory_iterator(".")) {
            if ((user.name+"_4x4_save.txt")==(entry.path().filename())){
                string option;
                cout<<"Do you want to continue your last saved game? (y/n): ";
                getline(cin, option);

                // Validate load choice input
                while(option!="Y"&&option!="y"&&option!="n"&&option!="N"){
                    cout<<"Invalid input. Please enter y or n: ";
                    getline(cin, option);
                }
                if(option=="Y"||option=="y"){
                    ifstream fin;
                    fin.open(user.name+"_4x4_save.txt");
                    if(fin.is_open()) { // Load game state from file
                        string savedLevel;
                        getline(fin, savedLevel);
                        game4x4->set_level(savedLevel);
                        fin >> game4x4->get_score_ref();
                        for(int i = 0; i < 4; i++) {
                            for(int j = 0; j < 4; j++) {
                                fin >> game4x4->get_board()[i][j];
                            }
                        }
                        loadedSave = true;
                        cout << "Game loaded successfully!\n";
                    }
                    fin.close();
                }
                break;
            }
        }

        // Initialize new game if no save loaded
        if(!loadedSave) {
            game4x4->reset();
            game4x4->set_level(level);
            game4x4->add_random();
            game4x4->add_random();
        }
        game4x4->print();

        // Main game loop
        while(gameRunning) {
            getline(cin, direction);

            // Validate movement input
            while(direction!="a" && direction!="w" && direction!="s" && direction!="d" && direction!="q"){
                cout<<"invalid direction. plz input wasd (or q to quit):";
                getline(cin, direction);
            }
            if(direction == "q") break;

            // Update game state
            game4x4->update(direction);
            clearScreen();
            game4x4->print();
            game4x4->add_random();
            game4x4->print();


            // Check game status
            string status = game4x4->check();
            if(status.find("reached") != string::npos) {
                cout << "Congratulations! You won!\n";
                if(game4x4->get_score() > user.highestScore4) {
                    user.highestScore4 = game4x4->get_score();
                    cout << "New personal best: " << game4x4->get_score()<< endl;
                    saveUser(user);
                }
                break;
            } else if(status == "lose") {
                cout << "Game Over!\n";
                if(game4x4->get_score() > user.highestScore4) {
                    user.highestScore4 = game4x4->get_score();
                    cout << "New personal best: " <<game4x4->get_score() << endl;
                    saveUser(user);
                }
                break;
            }
        }
        
        // Save game prompt
        cout << "Save game before quitting? (y/n): ";
        string saveChoice;
        getline(cin, saveChoice);
        if(saveChoice == "y" || saveChoice == "Y") {
            string filename = user.name + "_4x4_save.txt";
            game4x4->save_game(filename);
        }
        delete game4x4;
    }

    // 5x5 Game Version (structure identical to 4x4 with size differences)
    else if(gameChoice == "2") {
        game5x5 = new BigMennyPlus();
        bool loadedSave = false;
        for (const auto& entry : fs::directory_iterator(".")) {
            if ((user.name+"_5x5_save.txt")==(entry.path().filename())){
                string option;
                cout<<"Do you want to continue your last saved game? (y/n): ";
                getline(cin, option);
                while(option!="Y"&&option!="y"&&option!="n"&&option!="N"){
                    cout<<"Invalid input. Please enter y or n: ";
                    getline(cin, option);
                }
                if(option=="Y"||option=="y"){
                    ifstream fin;
                    fin.open(user.name+"_5x5_save.txt");
                    if(fin.is_open()) {
                        string savedLevel;
                        getline(fin, savedLevel);
                        game5x5->set_level(savedLevel);
                        fin >> game5x5->get_score_ref();
                        for(int i = 0; i < 5; i++) {
                            for(int j = 0; j < 5; j++) {
                                fin >> game5x5->get_board()[i][j];
                            }
                        }
                        loadedSave = true;
                        cout << "Game loaded successfully!\n";
                    }
                    fin.close();
                }
                break;
            }
        }
        if(!loadedSave) {
            game5x5->reset();
            game5x5->set_level(level);
            game5x5->add_random();
            game5x5->add_random();
        }
        game5x5->print();
        
        while(gameRunning) {
            getline(cin, direction);
            while(direction!="a" && direction!="w" && direction!="s" && direction!="d" && direction!="q"){
                cout<<"invalid direction. plz input wasd (or q to quit):";
                getline(cin, direction);
            }
            if(direction == "q") break;
            game5x5->update(direction);
            clearScreen();
            game5x5->print();
            game5x5->add_random();
            game5x5->print();
            
            string status = game5x5->check();
            if(status.find("reached") != string::npos) {
                cout << "Congratulations! You won!\n";
                if(game5x5->get_score() > user.highestScore5) {
                    user.highestScore5 = game5x5->get_score();
                    cout << "New personal best: " << game5x5->get_score()<< endl;
                    saveUser(user);
                }
                break;
            } else if(status == "lose") {
                cout << "Game Over!\n";
                if(game5x5->get_score() > user.highestScore5) {
                    user.highestScore5 = game5x5->get_score();
                    cout << "New personal best: " <<game5x5->get_score() << endl;
                    saveUser(user);
                }
                break;
            }
        }
        
        cout << "Save game before quitting? (y/n): ";
        string saveChoice;
        getline(cin, saveChoice);
        if(saveChoice == "y" || saveChoice == "Y") {
            string filename = user.name + "_5x5_save.txt";
            game5x5->save_game(filename);
        }
        delete game5x5;
    }

    // 6x6 Game Version (structure identical to 4x4 with size differences)
    else if(gameChoice == "3") {
        game6x6 = new BigMennyPro();
        bool loadedSave = false;
        for (const auto& entry : fs::directory_iterator(".")) {
            if ((user.name+"_6x6_save.txt")==(entry.path().filename())){
                string option;
                cout<<"Do you want to continue your last saved game? (y/n): ";
                getline(cin, option);
                while(option!="Y"&&option!="y"&&option!="n"&&option!="N"){
                    cout<<"Invalid input. Please enter y or n: ";
                    getline(cin, option);
                }
                if(option=="Y"||option=="y"){
                    ifstream fin;
                    fin.open(user.name+"_6x6_save.txt");
                    if(fin.is_open()) {
                        string savedLevel;
                        getline(fin, savedLevel);
                        game6x6->set_level(savedLevel);
                        fin >> game6x6->get_score_ref();
                        for(int i = 0; i < 6; i++) {
                            for(int j = 0; j < 6; j++) {
                                fin >> game6x6->get_board()[i][j];
                            }
                        }
                        loadedSave = true;
                        cout << "Game loaded successfully!\n";
                    }
                    fin.close();
                }
                break;
            }
        }
        if(!loadedSave) {
            game6x6->reset();
            game6x6->set_level(level);
            game6x6->add_random();
            game6x6->add_random();
        }
        game6x6->print();
        
        while(gameRunning) {
            getline(cin, direction);
            while(direction!="a" && direction!="w" && direction!="s" && direction!="d" && direction!="q"){
                cout<<"invalid direction. plz input wasd (or q to quit):";
                getline(cin, direction);
            }
            if(direction == "q") break;
            game6x6->update(direction);
            clearScreen();
            game6x6->print();
            game6x6->add_random();
            game6x6->print();
            
            string status = game6x6->check();
            if(status.find("reached") != string::npos) {
                cout << "Congratulations! You won!\n";
                if(game6x6->get_score() > user.highestScore6) {
                    user.highestScore6 = game6x6->get_score();
                    cout << "New personal best: " << game6x6->get_score()<< endl;
                    saveUser(user);
                }
                break;
            } else if(status == "lose") {
                cout << "Game Over!\n";
                if(game6x6->get_score() > user.highestScore6) {
                    user.highestScore6 = game6x6->get_score();
                    cout << "New personal best: " <<game6x6->get_score() << endl;
                    saveUser(user);
                }
                break;
            }
        }
        
        cout << "Save game before quitting? (y/n): ";
        string saveChoice;
        getline(cin, saveChoice);
        if(saveChoice == "y" || saveChoice == "Y") {
            string filename = user.name + "_6x6_save.txt";
            game6x6->save_game(filename);
        }
        delete game6x6;
    }

    return 0;
}
