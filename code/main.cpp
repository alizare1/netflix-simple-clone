#include "myServer.hpp"
#include "handlers.hpp"
#include <iostream>
#include <string>

using namespace std;


int main(int argc, char **argv) {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("pages/404.html");
    server.get("/", new RootDirHandler());
    server.get("/login", new TemplateHandler("pages/login.html"));
    server.post("/login", new LoginHandler());
    server.get("/signup", new TemplateHandler("pages/signup.html"));
    server.post("/signup", new SignupHandler());
    server.get("/home", new HomeDirHandler());
    server.get("/logout", new LogoutHandler());
    server.get("/newfilm", new NewFilmGet());
    server.post("/newfilm", new NewFilmPost());
    server.get("/deletefilm", new DeleteFilmHandler());
    server.post("/addmoney", new AddMoneyHandler());
    server.get("/profile", new ProfileHandler());
    server.get("/buy", new BuyHandler());
    server.get("/filminfo", new FilmInfoHandler());
    server.post("/comment", new CommentHandler());
    server.post("/rate", new RateHandler());
    server.run();
}