#include "request.h"

class Put : public Request {
public:
    void parseInput(StructedInput structedInput);

private:
    typedef void (Put::*functionPtr)(Args);
    std::map<std::string, functionPtr> functionMap;
};