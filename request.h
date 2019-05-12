#include "structedInput.h"
#include <map>
#include <string>
#include "defines.h"

class Request {
public: 
    virtual void parseInput(StructedInput& structedIput) = 0;

protected:
    // network
};