#ifndef POST_H
#define POST_H

#include <iostream>
#include "myReq.h"
#include "structs.h"
#include "exceptions.h"
#include "network.h"
#include <regex>

class Post : public MyRequest {
public:
    int signup(Args& args);
    int login(Args& args);
    void newFilm(Args& args, int sid);
    void doMoneyCommand(Args& args);
    void rateFilm(Args& args, std::string sid);
    void commentOnFilm(std::string content, std::string sid, std::string filmId);
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
    void deleteFilm(std::string filmId, std::string sid);
    void addMoney(std::string sid, std::string amount);
    void buyFilm(std::string sid, std::string filmId);

};

#endif