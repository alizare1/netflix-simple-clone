#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "structedInput.h"
#include "defines.h"
#include "post.h"
#include "get.h"
#include "put.h"
#include "delete.h"

// check for repeated arg?

class CommandInterface {
public:
    CommandInterface();
    void run();
private:
    std::vector<std::string> tokenize(std::string& line);
    StructedInput getStructedInput(std::vector<std::string>& input);
    bool isInputSizeGood(std::vector<std::string>& input);
    Args mapArgs(std::vector<std::string>& input);

    std::map<std::string, std::function<void(StructedInput)>> functionMap;
    Post POST;
    Delete DELETE;
    Get GET;
    Put PUT;
};