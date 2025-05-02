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
using namespace std;

/**
 * Clears the console screen in a cross-platform manner.
 * For Windows: Uses WinAPI console functions
 * For other platforms: Uses ANSI escape codes
 * Input: None
 * Output: None (clears the screen)
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
 * Main function that drives the 2048 game application.
 * Handles user registration/login, game selection, difficulty selection,
 * and manages the game loop for different game versions.
 * Input: None (command line execution)
 * Output: Returns 0 on successful program completion
 */
int main() {
    vector<account> users;               // Stores all registered user accounts
    account* currentUser = nullptr;      // Pointer to currently logged in user
    
    // User login/registration system
    while(!currentUser) {
        cout << "1. Register\n2. Login\n3. Exit\nChoose: ";
        string choice;
        getline(cin, choice);
        
        // Validate user input
        while(choice != "1" && choice != "2" && choice != "3"){
            cout << "Invalid choice! Please enter again (1-3): ";
            getline(cin, choice);
        }
        
        if(choice == "1") {
            // Register new user
            account newUser;
            cout << "Enter username: ";
            getline(cin, newUser.name);
            newUser.id = static_cast<int>(users.size());
            newUser.highestScore = 0;
            users.push_back(newUser);
            currentUser = &users.back();
            cout << "Registered successfully!\n";
        } 
        else if(choice == "2") {
            // User login
            if(users.empty()) {
                cout << "No users registered yet!\n";
                continue;
            }
            
            cout << "Enter username: ";
            string username;
            getline(cin, username);
            
            // Search for user in registered users
            for(auto& user : users) {
                if(user.name == username) {
                    currentUser = &user;
                    cout << "Logged in as " << username << "\n";
                    break;
                }
            }
            
            if(!currentUser) {
                cout << "User not found!\n";
            }
        }
        else if(choice == "3") {
            return 0;  // Exit program
        }
    }

    // Game selection menu
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

    // Difficulty selection
    string level;
    cout << "\nSelect Difficulty:\n"
         << "1. Easy\n"
         << "2. Medium\n"
         << "3. Hard\n"
         << "Choice: ";
    string levelChoice;
    getline(cin, levelChoice);
    
    // Validate difficulty choice input
    while(levelChoice != "1" && levelChoice != "2" && levelChoice != "3"){
        cout << "Invalid choice! Please enter again (1-3): ";
        getline(cin, levelChoice);
    }
    
    // Set difficulty level based on choice
    if(levelChoice == "1") level = "easy";
    else if(levelChoice == "2") level = "medium";
    else level = "hard";

    // Initialize game based on user selection
    Menny* game4x4 = nullptr;        // Pointer to 4x4 game instance
    BigMennyPlus* game5x5 = nullptr; // Pointer to 5x5 game instance
    BigMennyPro* game6x6 = nullptr;  // Pointer to 6x6 game instance
    
    string direction;                // Stores user movement input (wasd)
    cout << "plz input wasd:";
    bool gameRunning = true;         // Flag to control game loop
    
    // 4x4 Game Version
    if(gameChoice == "1") {
        game4x4 = new Menny();
        game4x4->reset();
        game4x4->set_level(level);
        game4x4->add_random();
        game4x4->add_random();
        game4x4->print();
        
        // Main game loop
        while(gameRunning) {
            getline(cin, direction);
            if(direction == "q") break;  // Quit game
            
            // Validate movement input
            while(direction!="a" && direction!="w" && direction!="s" && direction!="d" && direction!="q"){
                cout<<"invalid direction. plz input wasd (or q to quit):";
                getline(cin, direction);
            }
            
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
                if(game4x4->get_score() > currentUser->highestScore) {
                    currentUser->highestScore = game4x4->get_score();
                    cout << "New personal best: " << currentUser->highestScore << endl;
                }
                break;
            } else if(status == "lose") {
                cout << "Game Over!\n";
                if(game4x4->get_score() > currentUser->highestScore) {
                    currentUser->highestScore = game4x4->get_score();
                    cout << "New personal best: " << currentUser->highestScore << endl;
                }
                break;
            }
        }
        
        // Save game prompt
        cout << "Save game before quitting? (y/n): ";
        string saveChoice;
        getline(cin, saveChoice);
        if(saveChoice == "y" || saveChoice == "Y") {
            string filename = currentUser->name + "_4x4_save.txt";
            game4x4->save_game(filename);
        }
        delete game4x4;
    }
    // 5x5 Game Version
    else if(gameChoice == "2") {
        game5x5 = new BigMennyPlus();
        game5x5->reset();
        game5x5->set_level(level);
        game5x5->add_random();
        game5x5->add_random();
        game5x5->print();
        
        while(gameRunning) {
            getline(cin, direction);
            if(direction == "q") break;
            while(direction!="a" && direction!="w" && direction!="s" && direction!="d" && direction!="q"){
                cout<<"invalid direction. plz input wasd (or q to quit):";
                getline(cin, direction);
            }
            
            game5x5->update(direction);
            clearScreen();
            game5x5->print();
            game5x5->add_random();
            game5x5->print();
            
            string status = game5x5->check();
            if(status.find("reached") != string::npos) {
                cout << "Congratulations! You won!\n";
                if(game5x5->get_score() > currentUser->highestScore) {
                    currentUser->highestScore = game5x5->get_score();
                    cout << "New personal best: " << currentUser->highestScore << endl;
                }
                game5x5->save_highscore();
                break;
            } else if(status == "lose") {
                cout << "Game Over!\n";
                if(game5x5->get_score() > currentUser->highestScore) {
                    currentUser->highestScore = game5x5->get_score();
                    cout << "New personal best: " << currentUser->highestScore << endl;
                }
                break;
            }
        }
        
        cout << "Save game before quitting? (y/n): ";
        string saveChoice;
        getline(cin, saveChoice);
        if(saveChoice == "y" || saveChoice == "Y") {
            string filename = currentUser->name + "_5x5_save.txt";
            game5x5->save_game(filename);
        }
        delete game5x5;
    }
    // 6x6 Game Version
    else if(gameChoice == "3") {
        game6x6 = new BigMennyPro();
        game6x6->reset();
        game6x6->set_level(level);
        game6x6->add_random();
        game6x6->add_random();
        game6x6->print();
        
        while(gameRunning) {
            getline(cin, direction);
            if(direction == "q") break;
            while(direction!="a" && direction!="w" && direction!="s" && direction!="d" && direction!="q"){
                cout<<"invalid direction. plz input wasd (or q to quit):";
                getline(cin, direction);
            }
            
            game6x6->update(direction);
            clearScreen();
            game6x6->print();
            game6x6->add_random();
            game6x6->print();
            
            string status = game6x6->check();
            if(status.find("reached") != string::npos) {
                cout << "Congratulations! You won!\n";
                if(game6x6->get_score() > currentUser->highestScore) {
                    currentUser->highestScore = game6x6->get_score();
                    cout << "New personal best: " << currentUser->highestScore << endl;
                }
                break;
            } else if(status == "lose") {
                cout << "Game Over!\n";
                if(game6x6->get_score() > currentUser->highestScore) {
                    currentUser->highestScore = game6x6->get_score();
                    cout << "New personal best: " << currentUser->highestScore << endl;
                }
                break;
            }
        }
        
        cout << "Save game before quitting? (y/n): ";
        string saveChoice;
        getline(cin, saveChoice);
        if(saveChoice == "y" || saveChoice == "Y") {
            string filename = currentUser->name + "_6x6_save.txt";
            game6x6->save_game(filename);
        }
        delete game6x6;
    }

    return 0;
}
