#ifndef REGISTERUSER_H
#define REGISTERUSER_H

#include <vector>
#include <string>

struct account {
    int id;
    std::string name;
    int highestScore;
};

void registerUser(std::vector<account>& users);
#endif 
