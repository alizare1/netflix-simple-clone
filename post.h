#ifndef POST_H
#define POST_H

#include <iostream>
#include "request.h"
#include "structs.h"
#include "exceptions.h"
#include "network.h"
#include <regex>

class Post : public Request {
public:
    Post(Network* _network);

private:
    void signup(Args& args);
    void login(Args& args);
    void newFilm(Args& args);
    void doMoneyCommand(Args& args);
    void replyToComment(Args& args);
    void followUser(Args& args);
    void buyFilm(Args& args);
    void rateFilm(Args& args);
    void commentOnFilm(Args& args);
    SignupArgs getSignupArgs(Args& args);
    LoginArgs getLoginArgs (Args& args);
    NewFilmArgs getNewFilmArgs(Args& args);
    ReplyArgs getReplyArgs(Args& args);
    RateArgs getRateArgs(Args& args);
    CommentArgs getCommentArgs(Args& args);
    std::string hashString(const std::string& str);
    bool isEmailValid(const std::string email);
    void editFilm(Args& args);
    EditFilmArgs getFilmArgs(Args& args);
    void deleteFilm(Args& args);
    void deleteComment(Args& args);
    DeleteCommentArgs getDeleteCommentArgs(Args& args);
    void logout();

};

#endif