#include "request.h"

class Delete : public Request {
public:
    void parseInput(StructedInput structedInput);

private:
    typedef void (Delete::*functionPtr)(Args);
    std::map<std::string, functionPtr> functionMap;
};