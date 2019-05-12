#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <structedInput.h>
#include <defines.h>

// check for repeated arg?

class CommandInterface {
public:
    void run();
private:
    std::vector<std::string> tokenize(std::string& line);
    StructedInput getStructedInput(std::vector<std::string>& input);
    bool isInputSizeGood(std::vector<std::string>& input);
    std::map<std::string, std::string> mapArgs(std::vector<std::string>& input);

};