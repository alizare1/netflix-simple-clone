#include "request.h"

class Get : public Request {
public:
    void parseInput(StructedInput structedInput);

private:
    typedef void (Get::*functionPtr)(Args);
    std::map<std::string, functionPtr> functionMap;
};