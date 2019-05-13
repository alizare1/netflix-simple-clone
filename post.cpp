#include "post.h"

using namespace std;

Post::Post() {
    functionMap[SIGNUP] =
        [this](Args args){ signup(args); };
    functionMap[LOGIN] = 
        [this](Args args){ login(args); };
    functionMap[FILMS] =
        [this](Args args){ newFilm(args); };
}

void Post::parseInput(StructedInput& StructedInput) {
    if (functionMap.find(StructedInput.command) != functionMap.end())
        functionMap[StructedInput.command](StructedInput.args);
    else 
        ; // throw not found exception
}

void Post::signup(Args& args) {
    SignupArgs signupArgs = getSignupArgs(args);
    // network->signup() ;
}

void Post::login(Args& args) {
    LoginArgs loginArgs = getLoginArgs(args);
    // network->loging();
}

void Post::newFilm(Args& args) {

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
        //     signupArgs.age = stoi(args.at(AGE)) : throw bad req exception ;
        signupArgs.age = stoi(args.at(AGE));
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

LoginArgs Post::getLoginArgs(Args& args) {
    LoginArgs loginArgs;
    try {
        loginArgs.username = args.at(USERNAME);
        loginArgs.password = hashString(args.at(PASSWORD));
    }
    catch (exception& e) {
        ; // throw bad req exception
    }
    return loginArgs;
}

NewFilmArgs Post::getNewFilmArgs(Args& args) {
    NewFilmArgs newFilmArgs;
    try {
        newFilmArgs.summary = args.at(SUMMARY);
        newFilmArgs.director = args.at(DIRECTOR);
        newFilmArgs.name = args.at(NAME);
        // isNumber(args.at(PRICE)) ?
        //     signupArgs.price = stoi(args.at(PRICE)) : throw bad req exception ;
        // isNumber(args.at(YEAR)) ?
        //     signupArgs.year = stoi(args.at(YEAR)) : throw bad req exception ;
        // isNumber(args.at(LENGTH)) ?
        //     signupArgs.length = stoi(args.at(LENGHT)) : throw bad req exception ;
        newFilmArgs.price = stoi(args.at(PRICE));
        newFilmArgs.year = stoi(args.at(PRICE));
        newFilmArgs.length = stoi(args.at(LENGTH));
    }
    catch (exception& e) {
        ; // trhow bad req exception ;
    }
    return newFilmArgs;
}