#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "../server/server.hpp"
#include "../backendCode/get.h"
#include "../backendCode/post.h"
#include <iostream>
#include <map>

class CustomReqHandler : public RequestHandler {
protected:
    Post POST;
    Get GET;
};

class CustomTempHandler : public TemplateHandler {
public:
    CustomTempHandler(std::string path) : TemplateHandler(path){}
    virtual std::map<std::string, std::string> handle(Request *req);
protected:
    Post POST;
    Get GET;
};

class RootDirHandler : public CustomReqHandler {
public:
    Response* callback(Request* req);
    std::map<std::string, std::string> handle(Request *req);
};

class SignupHandler : public CustomReqHandler {
    Response* callback(Request* req);
};

class LoginHandler : public CustomReqHandler {
    Response* callback(Request* req);
};

class HomeDirHandler : public CustomReqHandler {
public:
    Response* callback(Request* req);
private:
    std::map<std::string, std::string> createContext(Request* req);
};

class LogoutHandler : public CustomReqHandler {
    Response* callback(Request* req);
};

class NewFilmGet : public CustomReqHandler {
    Response* callback(Request* req);
};

class NewFilmPost : public CustomReqHandler {
    Response* callback(Request* req);
};

class DeleteFilmHandler : public CustomReqHandler {
    Response* callback(Request* req);
};

class AddMoneyHandler : public CustomReqHandler {
    Response* callback(Request* req);
};

class ProfileHandler : public CustomReqHandler {
    Response* callback(Request* req);
    std::map<std::string, std::string> createContext(Request* req);
};

class BuyHandler : public CustomReqHandler {
    Response* callback(Request* req);
};

class FilmInfoHandler : public CustomReqHandler {
    Response* callback(Request* req);
    std::map<std::string, std::string> createContext(Request* req);
};

class CommentHandler : public CustomReqHandler {
    Response* callback(Request* req);
};

class RateHandler : public CustomReqHandler {
    Response* callback(Request* req);
};

#endif