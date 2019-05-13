#ifndef REQUEST_H
#define REQUEST_H

#include "structs.h"
#include <map>
#include <string>
#include <functional>
#include "defines.h"

class Request {
public: 
    virtual void parseInput(StructedInput& structedIput) = 0;

protected:
    // network
};

#endif