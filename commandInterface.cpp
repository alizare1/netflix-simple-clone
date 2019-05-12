#include <commandInterface.h>

using namespace std;


void CommandInterface::run() {
    string line;
    vector<string> input;
    StructedInput structedInput;
    while (getline(cin, line)) {
        input = tokenize(line);
        structedInput = getStructedInput(input);
        
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
    return tokenized;
}

StructedInput CommandInterface::getStructedInput(vector<string>& input) {
    if (!isInputSizeGood(input) || input[2] != QUESTION_MARK)
        ; // throw bad req exception
    StructedInput structedInput;
    structedInput.method = input[0];
    structedInput.command = input[1];
    structedInput.args = mapArgs(input);
}

bool CommandInterface::isInputSizeGood(vector<string>& input) {
    if (input.size() - 3 % 2 == 0) 
        return true;
    return false;
}

map<string,string> CommandInterface::mapArgs(vector<string>& input) {
    map<string, string> args;
    for (int i = 3; i < input.size() - 1; i += 2) {
        args.insert(make_pair(input[i], input[i + 1]));
    }
    return args;
}