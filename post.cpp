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
        // isEmailValid(args.at(EMAIL)) ? 
            // signupArgs.email = args.at(EMAIL) : throw bad req exception ;
        signupArgs.email = args.at(EMAIL);
        // isNumber(args.at(AGE)) ?
        //     signupArgs.age = args.at(AGE) : throw bad req exception ;
        signupArgs.age = args.at(AGE);
        if (args.find(PUBLISHER) != args.end())
            if (args.at(PUBLISHER) == TRUE || args.at(PUBLISHER) == FALSE)
                signupArgs.publisher = args.at(PUBLISHER);
            else 
                ; // throw bad req exception
        else 
            signupArgs.publisher = FALSE;
    }
    catch (exception& e) {
        ; // throw bad req exception
    }
    return signupArgs;
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

bool Post::isEmailValid(const std::string email) {
   const std::regex pattern
      ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
   return std::regex_match(email, pattern);
}