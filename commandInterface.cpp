#include "commandInterface.h"
#include "network.h"

using namespace std;

CommandInterface::CommandInterface(Network* network)
    :POST(network), GET(network) {
    functionMap[POST_STR] = 
        [this](StructedInput structedInput){POST.parseInput(structedInput);};
    functionMap[GET_STR] = 
        [this](StructedInput structedInput){GET.parseInput(structedInput);};
}

void CommandInterface::run() {
    string line;
    vector<string> input;
    StructedInput structedInput;
    while (getline(cin, line)) {
        input = tokenize(line);
        if (input.size() == 0)
            continue;
        try {
            structedInput = getStructedInput(input);
            functionMap[structedInput.method](structedInput);
        }
        catch (exception& e) {
            cout << e.what();
        }
    }
}

vector<string> CommandInterface::tokenize(string& line) {
    vector<string> tokenized;
    for (int i = 0; i < line.size(); i++) {
        string word;
        while (i < line.size() && line[i] == ' ') i++;
        while (line[i] != ' ' && i < line.size() ) word += line[i++];
        if (!word.empty())
            tokenized.push_back(word);
        word = "";
    }
    checkNotifRead(tokenized);
    return tokenized;
}

StructedInput CommandInterface::getStructedInput(vector<string>& input) {
    if (!isReqGood(input))
        throw BadRequest();
    StructedInput structedInput;
    structedInput.method = input[0];
    structedInput.command = input[1];
    if (hasArgs(input))
        structedInput.args = mapArgs(input);
    return structedInput;
}

bool CommandInterface::isReqGood(vector<string>& input) {
    if (input.size() < 2)
        return false;
    if (functionMap.find(input[0]) == functionMap.end())
        return false;
    if (input.size() == 2)
        return true;
    if (input[2] != QUESTION_MARK)
        return false;
    return isInputSizeGood(input);

}

bool CommandInterface::isInputSizeGood(vector<string>& input) {
    if ((input.size() - 3) % 2 == 0) 
        return true;
    return false;
}

bool CommandInterface::hasArgs(vector<string>& input) {
    if (input.size() > 2)
        return true;
    return false;
}

map<string,string> CommandInterface::mapArgs(vector<string>& input) {
    map<string, string> args;
    for (int i = 3; i < input.size() - 1; i += 2) {
        if (args.count(input[i]))
            throw BadRequest();
        args.insert(make_pair(input[i], input[i + 1]));
    }
    return args;
}

void CommandInterface::checkNotifRead(vector<string>& input) {
    if (input.size() < 6)
        return;
    if (input[0] == GET_STR && input[1] == NOTIFICATION && 
        input[3] == QUESTION_MARK && input[2] == READ) {
        input[1] = NOTIFICATION_READ;
        input.erase(input.begin() + 2);
    }
}

