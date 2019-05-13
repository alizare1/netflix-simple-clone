#include "post.h"

using namespace std;

Post::Post() {
    functionMap[SIGNUP] =
        [this](Args args){signup(args);};
}

void Post::parseInput(StructedInput& StructedInput) {
    if (functionMap.find(StructedInput.command) != functionMap.end())
        functionMap[StructedInput.command](StructedInput.args);
    else 
        ; // throw not found exception
}

void Post::signup(Args& args) {
    SignupArgs signupArgs = getSignupArgs(args);
    
}

SignupArgs Post::getSignupArgs(Args& args) {
    SignupArgs signupArgs;
    try {
        signupArgs.username = args.at(USERNAME);
        signupArgs.password = hashString(args.at(PASSWORD));
        signupArgs.email = args.at(EMAIL);
        signupArgs.age = args.at(AGE);
        if (args.find(PUBLISHER) != args.end())
            signupArgs.publisher = args.at(PUBLISHER);
        else 
            signupArgs.publisher = FALSE;
    }
    catch (exception& e) {
        ; // throw bad req exception
    }
}

std::string Post::hashString(const std::string& str) {
    const int prime = 1027;
    const int mod = 1e9 + 9;
    long long hashedStr = 0;
    long long primePow = 1;
    for (char c : str) {
        hashedStr = (hashedStr + (c - 'a' + 1) * primePow) % mod;
        primePow = (primePow * prime) % mod;
    }
    return to_string(hashedStr);
}