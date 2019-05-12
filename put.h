#ifndef PUT_H
#define PUT_H

#include "request.h"

class Put : public Request {
public:
    void parseInput(StructedInput& structedInput);

private:
    std::map<std::string, std::function<void(StructedInput)>> functionMap;
};

#endif