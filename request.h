#ifndef REQUEST_H
#define REQUEST_H

#include "structs.h"
#include <map>
#include <string>
#include <functional>
#include "defines.h"
#include "exceptions.h"

class Request {
public: 
    virtual void parseInput(StructedInput& structedIput) = 0;

protected:
    // network
    bool isNumber(std::string str);
    bool mapHasKey(std::map<std::string, std::string>& keyMap, std::string key);
};

#endif