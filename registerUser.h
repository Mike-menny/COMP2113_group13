#ifndef REGISTERUSER_H
#define REGISTERUSER_H

#include <vector>
#include <string>

struct account {
    std::string name;
    int highestScore4;
    int highestScore5;
    int highestScore6;
};

bool checkuser(std::string name);
account registerUser();
void readuser(std::string filename, account &user);
void saveUser(account &user);

#endif 
