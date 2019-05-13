#ifndef COM_INTERFACE_H
#define COM_INTERFACE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "structs.h"
#include "defines.h"
#include "post.h"
#include "get.h"
#include "put.h"
#include "delete.h"
#include "exceptions.h"

class CommandInterface {
public:
    CommandInterface();
    void run();
private:
    std::vector<std::string> tokenize(std::string& line);
    StructedInput getStructedInput(std::vector<std::string>& input);
    bool isInputSizeGood(std::vector<std::string>& input);
    Args mapArgs(std::vector<std::string>& input);
    bool isReqGood(std::vector<std::string>& input);
    bool hasArgs(std::vector<std::string>& input);

    std::map<std::string, std::function<void(StructedInput)>> functionMap;
    Post POST;
    Delete DELETE;
    Get GET;
    Put PUT;
};


#endif