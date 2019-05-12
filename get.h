#include "request.h"

class Get : public Request {
public:
    void parseInput(StructedInput& structedInput);

private:
    std::map<std::string, std::function<void(StructedInput)>> functionMap;
};