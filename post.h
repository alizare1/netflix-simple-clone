#include "request.h"

class Post : public Request {
public:
    void parseInput(StructedInput structedInput);

private:
    typedef void (Post::*functionPtr)(Args);
    std::map<std::string, functionPtr> functionMap;
};