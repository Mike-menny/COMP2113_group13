#ifndef REGISTERUSER_H
#define REGISTERUSER_H

#include <vector>

struct account {
    int id;
    std::string name;
    int highestScore;
};

void registerUser(std::vector<account>& users);
#endif 
