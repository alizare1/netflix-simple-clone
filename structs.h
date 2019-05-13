#ifndef STRUCTS_H
#define STRUCTS_H

#include <map>
#include <string>
#include "defines.h"

struct StructedInput {
    std::string method;
    std::string command;
    Args args;
};

struct SignupArgs {
    std::string email;
    std::string username;
    std::string password;
    std::string age;
    std::string publisher; 
};

#endif