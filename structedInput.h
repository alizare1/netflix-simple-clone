#ifndef STRUCTED_INPUT_H
#define STRUCTED_INPUT_H

#include <map>
#include <string>
#include "defines.h"

struct StructedInput {
    std::string method;
    std::string command;
    Args args;
};

#endif