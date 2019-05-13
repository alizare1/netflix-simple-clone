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
        signupArgs.password = args.at(PASSWORD);
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
