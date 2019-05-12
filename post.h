#ifndef POST_H
#define POST_H

#include "request.h"

class Post : public Request {
public:
    void parseInput(StructedInput& structedInput);

private:
    std::map<std::string, std::function<void(StructedInput)> > functionMap;
};

#endif