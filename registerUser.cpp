#include <iostream>
#include <vector>
#include <fstream>
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;
using namespace std;

struct account {
  string name;
  int highestScore4;
  int highestScore5;
  int highestScore6;
};
/**
 * @param users the user record vector
 * @return none, since user record have been passed by reference
 */

bool checkuser(string name){
  for (const auto& entry : fs::directory_iterator(".")) {
    if ((name+".txt")==(entry.path().filename())){
      return true;
    }
  }
  return false;
}

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

