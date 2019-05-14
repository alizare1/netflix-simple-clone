#include "request.h"



void Request::parseInput(StructedInput& structedInput) {
    if (functionMapHasCommand(structedInput.command))
        functionMap[structedInput.command](structedInput.args);
    else 
        throw NotFound();
}

bool Request::isNumber(std::string str) {
    for (int i = 0; i < str.size() ; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

bool Request::mapHasKey(std::map<std::string, std::string>& keyMap, std::string key) {
    if (keyMap.find(key) != keyMap.end())
        return true;
    return false;
}

bool Request::functionMapHasCommand(std::string& command) {
    if (functionMap.find(command) != functionMap.end())
        return true;
    return false;
}