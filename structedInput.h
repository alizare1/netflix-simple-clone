#include <map>
#include <string>

struct StructedInput {
    std::string method;
    std::string command;
    std::map<std::string, std::string> args;
};