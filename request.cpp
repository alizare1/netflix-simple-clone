#include "request.h"



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