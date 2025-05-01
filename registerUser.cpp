#include <iostream>
#include <vector>
using namespace std;

struct account {
  int id;
  string name;
  int highestScore;
};
/**
 * The registerUser function adds a new user to the user record vector.alignas
 * @param users the user record vector
 * @return none, since user record have been passed by reference
 */
void registerUser(vector<account>& users) {
  cout << "Enter your name:\n";
  string name;
  getline(cin, name);
  account Acc = {users.size(), name, 0};
  users.push_back(Acc);
}
