#ifndef registerUser_H
#define registerUser_H
#include <iostream>
#include <vector>

struct account {
    int id;
    std::string name;
    int highestScore;
};

void registerUser(std::vector<account>& users);
#endif 
