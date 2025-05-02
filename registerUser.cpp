#include <iostream>
#include <vector>
#include <fstream>
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;
using namespace std;

/**
 * @struct account
 * @brief Stores player account information including name and highest scores for different levels
 * 
 * @var account::name 
 * The player's username
 * @var account::highestScore4
 * Highest score achieved on level 4
 * @var account::highestScore5 
 * Highest score achieved on level 5
 * @var account::highestScore6
 * Highest score achieved on level 6
 */
struct account {
  string name;
  int highestScore4;
  int highestScore5;
  int highestScore6;
};

/**
 * @brief Checks if a username already exists by looking for corresponding .txt files
 * 
 * @param name The username to check for availability
 * @return true if username is already taken (file exists), false otherwise
 */
bool checkuser(string name){
  for (const auto& entry : fs::directory_iterator(".")) {
    if ((name+".txt")==(entry.path().filename())){
      return true;
    }
  }
  return false;
}

/**
 * @brief Registers a new user by creating an account structure and saving file
 * 
 * @return account The newly created user account
 * @note Prompts for username and verifies it's unique before creating
 * @warning Will continue prompting until unique username is provided
 */
account registerUser() {
  account user;
  user.highestScore4 = 0;
  user.highestScore5 = 0;
  user.highestScore6 = 0;
  cout << "Enter your name:\n";
  string name;
  getline(cin, name);
  while(checkuser(name)){
    cout<<"Username already used, please use another one: ";
    getline(cin, name);
  }
  user.name = name;
  ofstream fout;
  fout.open(name+".txt");
  fout<<name<<endl;
  fout<<0<<endl<<0<<endl<<0<<endl;
  fout.close();
  return user;
}

/**
 * @brief Loads user data from file into an account structure
 * 
 * @param filename The name of the user's data file (username.txt)
 * @param user Reference to account struct where data will be loaded
 * @note File format must be: name\nscore4\nscore5\nscore6
 * @warning Does not validate file contents, assumes proper formatting
 */
void readuser(string filename, account &user){
  ifstream fin;
  fin.open(filename);
  if(fin.is_open()) {
    getline(fin, user.name);
    fin>>user.highestScore4;
    fin>>user.highestScore5;
    fin>>user.highestScore6;
    fin.close();
  }
}

/**
 * @brief Saves user account data to their personal file
 * 
 * @param user Reference to account struct containing data to save
 * @note Creates or overwrites file in format: name\nscore4\nscore5\nscore6
 * @warning Will overwrite existing file without confirmation
 */
void saveUser(account &user){
  ofstream fout;
  fout.open(user.name+".txt");
  if(fout.is_open()) {
    fout << user.name << endl;
    fout << user.highestScore4 << endl;
    fout << user.highestScore5 << endl;
    fout << user.highestScore6 << endl;
    fout.close();
  } else {
    cerr << "Error: Could not save user data to file." << endl;
  }
}
