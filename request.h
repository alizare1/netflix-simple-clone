#ifndef REQUEST_H
#define REQUEST_H

#include "structs.h"
#include <map>
#include <string>
#include <functional>
#include <iostream>
#include "defines.h"
#include "exceptions.h"

typedef std::map<std::string, std::function<void(Args)> > FunctionMap;

class Request {
public: 
    void parseInput(StructedInput& structedInput);

protected:
    // network
    bool isNumber(std::string str);
    bool functionMapHasCommand(std::string& command);
    bool mapHasKey(std::map<std::string, std::string>& keyMap, std::string key);

    FunctionMap functionMap;
};

#endif