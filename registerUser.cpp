#include <iostream>
#include <vector>
using namespace std;

struct account {
  int id;
  string name;
  int highestScore;
};

void registerUser(vector<account>& users) {
  cout << "Enter your name:\n";
  string name;
  getline(cin, name);
  account Acc = {users.size(), name, 0};
  users.push_back(Acc);
}
