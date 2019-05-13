#ifndef POST_H
#define POST_H

#include <iostream>
#include "request.h"
#include "structs.h"

class Post : public Request {
public:
    Post();
    void parseInput(StructedInput& structedInput);

private:
    void signup(Args& args);
    SignupArgs getSignupArgs(Args& args);

    std::map<std::string, std::function<void(Args)> > functionMap;
};

#endif