#include "post.h"

using namespace std;

int Post::signup(Args& args) {
    SignupArgs signupArgs = getSignupArgs(args);
    return network->signup(signupArgs) ;
}

int Post::login(Args& args) {
    LoginArgs loginArgs = getLoginArgs(args);
    return network->login(loginArgs);
}

void Post::newFilm(Args& args, int sid) {
    NewFilmArgs newFilmArgs = getNewFilmArgs(args);
    network->addNewFilm(newFilmArgs, sid);
}

void Post::rateFilm(Args& args, string sid) {
    RateArgs rateArgs = getRateArgs(args);
    network->rateFilm(rateArgs, stoi(sid));
}

void Post::commentOnFilm(string content, string sid, string filmId) {
    network->commentOnFilm(content, stoi(sid), stoi(filmId));
}

SignupArgs Post::getSignupArgs(Args& args) {
    SignupArgs signupArgs;

    signupArgs.username = args.at(USERNAME);
    signupArgs.password = hashString(args.at(PASSWORD));
    signupArgs.email = args[EMAIL];
    signupArgs.age = stoi(args[AGE]);
    if (args.at(PUBLISHER) == TRUE)
        signupArgs.publisher = true;
    else if(args.at(PUBLISHER) == FALSE)
        signupArgs.publisher = false;

    return signupArgs;
}

string Post::hashString(const std::string& str) {
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
    loginArgs.username = args[USERNAME];
    loginArgs.password = hashString(args[PASSWORD]);
    return loginArgs;
}

NewFilmArgs Post::getNewFilmArgs(Args& args) {
    NewFilmArgs newFilmArgs;
    
    newFilmArgs.summary = args.at(SUMMARY);
    newFilmArgs.director = args.at(DIRECTOR);
    newFilmArgs.name = args.at(NAME);
    newFilmArgs.price = stoi(args.at(PRICE));
    newFilmArgs.year = stoi(args.at(YEAR));
    newFilmArgs.length = stoi(args.at(LENGTH));

    return newFilmArgs;
}

ReplyArgs Post::getReplyArgs(Args& args) {
    ReplyArgs replyArgs;
    try {
        replyArgs.content = args.at(CONTENT);
        isNumber(args.at(FILM_ID)) ?
            replyArgs.filmId = stoi(args.at(FILM_ID)) : throw BadRequest();
        isNumber(args.at(COMMENT_ID)) ?
            replyArgs.commentId = stoi(args.at(COMMENT_ID)) : throw BadRequest(); 
    }
    catch (exception& e) {
        throw BadRequest();
    }
    return replyArgs;
}

RateArgs Post::getRateArgs(Args& args) {
    RateArgs rateArgs;
    try {
        isNumber(args.at(SCORE)) ?
            rateArgs.score = stoi(args.at(SCORE)) : throw BadRequest();
        isNumber(args.at(FILM_ID)) ?
            rateArgs.filmId = stoi(args.at(FILM_ID)) : throw BadRequest();
    }
    catch(exception &e) {
        throw BadRequest();
    }
    return rateArgs;
}

CommentArgs Post::getCommentArgs(Args& args) {
    CommentArgs commentArgs;
    try {
        commentArgs.content = args.at(CONTENT);
        isNumber(args.at(FILM_ID)) ?
            commentArgs.filmId = stoi(args.at(FILM_ID)) : throw BadRequest();
    }
    catch (exception& e) {
        throw BadRequest();
    }
    return commentArgs;
}

EditFilmArgs Post::getFilmArgs(Args& args) {
    EditFilmArgs filmArgs;
    try {
        isNumber(args.at(FILM_ID)) ?
            filmArgs.filmId = stoi(args.at(FILM_ID)) : throw BadRequest();
    }
    catch(exception& e) {
        throw BadRequest();
    }
    if (args.count(NAME)) 
        filmArgs.name = args[NAME];
    if (args.count(SUMMARY))
        filmArgs.summary = args[SUMMARY];
    if (args.count(DIRECTOR)) 
        filmArgs.director = args[DIRECTOR];
    if (args.count(YEAR))
        isNumber(args.at(YEAR)) ?
            filmArgs.year = stoi(args.at(YEAR)) : throw BadRequest();
    if (args.count(LENGTH))
        isNumber(args.at(LENGTH)) ?
            filmArgs.length = stoi(args.at(LENGTH)) : throw BadRequest();
    if (args.count(PRICE))
        isNumber(args.at(PRICE)) ?
            filmArgs.price = stoi(args.at(PRICE)) : throw BadRequest();
    return filmArgs;
}

void Post::deleteFilm(string filmId, string sid) {
    network->deleteFilm(stoi(filmId), stoi(sid));
}

void Post::addMoney(string sid, string amount) {
    network->addMoney(stoi(sid), stoi(amount));
}

void Post::buyFilm(string sid, string filmId) {
    network->buyFilm(stoi(sid), stoi(filmId));
}