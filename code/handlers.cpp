#include "handlers.hpp"

using namespace std;

Response* RootDirHandler::callback(Request* req) {
    Response* r = new Response();
    if (req->getSessionId() == "") 
        r = Response::redirect("/login");
    else 
        r = Response::redirect("/home");
    return r;
}

Response* SignupHandler::callback(Request* req) {
    map<string, string> args = req->getParamsMap();
    map<string, string> errors;
    Response* r;
    TemplateParser* parser = new TemplateParser("pages/signup.html");
    if (args["password"] != args["reppassword"]) {
        errors["passwordExp"] = "Passwords must be the Same!";
        r = new Response();
        r->setHeader("Content-Type", "text/html");
        r->setBody(parser->getHtml(errors));
        TemplateParser::emptyMapFile();
        delete parser;
        return r;
    }
    if (args.count(PUBLISHER))
        args[PUBLISHER] = TRUE;
    else
        args[PUBLISHER] = FALSE;
    
    int userId;
    try {
        userId = POST.signup(args);
    }
    catch (exception& e) {
        Response* r = new Response();
        errors["usernameExists"] = "Username already exists!";
        r->setHeader("Content-Type", "text/html");
        r->setBody(parser->getHtml(errors));
        TemplateParser::emptyMapFile();
        delete parser;
        return r;
    }
    r = Response::redirect("/home");
    r->setSessionId(to_string(userId));
    delete parser;
    return r;
}

Response* LoginHandler::callback(Request* req) {
    map<string, string> args = req->getParamsMap();
    map<string, string> errors;
    Response* r;
    TemplateParser* parser = new TemplateParser("pages/login.html");
    int userId;
    try {
        userId = POST.login(args);
    }
    catch (exception& e) {
        errors["error"] = "Username or password is incorrect!";
        r = new Response();
        r->setHeader("Content-type", "text/html");
        r->setBody(parser->getHtml(errors));
        delete parser;
        TemplateParser::emptyMapFile();
        return r;
    }
    r = Response::redirect("/home");
    r->setSessionId(to_string(userId));
    return r;
}

Response* LogoutHandler::callback(Request* req) {
    Response* r = Response::redirect("/");
    r->setSessionId("");
    return r;
}

Response* NewFilmGet::callback(Request* req) {
    Response* r;
    if (req->getSessionId() == "" || !GET.isPublisher(req->getSessionId()))
        r = ShowPage("pages/permdenied.html").callback(req);
    else {
        r = new Response();
        map<string, string> context;
        context[USERNAME] = GET.getUsername(req->getSessionId());
        TemplateParser* parser = new TemplateParser("pages/newfilm.html");
        r = new Response();
        r->setHeader("Content-Type", "text/html");
        r->setBody(parser->getHtml(context));
        TemplateParser::emptyMapFile();
        delete parser;
    }
    return r;
}

Response* NewFilmPost::callback(Request* req) {
    map<string, string> args = req->getParamsMap();
    POST.newFilm(args, stoi(req->getSessionId()));
    Response* r = Response::redirect("/home");
    return r;
}

Response* HomeDirHandler::callback(Request* req) {
    Response* r;
    if (req->getSessionId() == "")
        r = ShowPage("pages/permdenied.html").callback(req);
    else {
        map<string, string> context = createContext(req);
        TemplateParser* parser = new TemplateParser("pages/home.html");
        r = new Response();
        r->setHeader("Content-Type", "text/html");
        r->setBody(parser->getHtml(context));
        TemplateParser::emptyMapFile();
        delete parser;
    }
    return r;
}

map<string, string> HomeDirHandler::createContext(Request* req) {
    map<string, string> context;
    context["SID"] = req->getSessionId();
    if (GET.isPublisher(req->getSessionId())) {
        context[PUBLISHER] = TRUE;
        context[PUBLISHED] = GET.getPublishedFilms(context["SID"], req->getQueryParam(DIRECTOR));
    } else {
        context[FILMS] = GET.getAbleToBuyFilms(req->getSessionId());
    }
    context[USERNAME] = GET.getUsername(context["SID"]);
    return context;
}

Response* DeleteFilmHandler::callback(Request* req) {
    Response* r = Response::redirect("/home");
    if (req->getSessionId() == "")
        r  = ShowPage("pages/permdenied.html").callback(req);
    try {
        POST.deleteFilm(req->getQueryParam("id") ,req->getSessionId());
    }
    catch (exception& e) {
        r = ShowPage("pages/permdenied.html").callback(req);
    }
    return r;
}

Response* AddMoneyHandler::callback(Request* req) {
    POST.addMoney(req->getSessionId(), req->getBodyParam(AMOUNT));
    Response* r = Response::redirect("/profile");
    return r;
}

Response* ProfileHandler::callback(Request* req) {
    Response* r;
    if (req->getSessionId() == "")
        r = ShowPage("pages/permdenied.html").callback(req);
    else {
        map<string, string> context = createContext(req);
        TemplateParser* parser = new TemplateParser("pages/profile.html");
        r = new Response();
        r->setHeader("Content-Type", "text/html");
        r->setBody(parser->getHtml(context));
        TemplateParser::emptyMapFile();
        delete parser;
    }
    return r;
}

map<string, string> ProfileHandler::createContext(Request* req) {
    map<string, string> context;
    context["SID"] = req->getSessionId();
    context[FILMS] = GET.getBoughtMovies(req->getSessionId());
    context[USERNAME] = GET.getUsername(context["SID"]);
    context[MONEY] = to_string(Network::getInstance()->getMoney(stoi(req->getSessionId())));
    return context;
}

Response* BuyHandler::callback(Request* req) {
    POST.buyFilm(req->getSessionId(), req->getQueryParam("id"));
    Response* r = Response::redirect("/filminfo?id=" + req->getQueryParam("id"));
    return r;
}

Response* FilmInfoHandler::callback(Request* req) {
    Response* r;
    map<string, string> context = createContext(req);
    TemplateParser* parser = new TemplateParser("pages/filminfo.html");
    r = new Response();
    r->setHeader("Content-Type", "text/html");
    r->setBody(parser->getHtml(context));
    TemplateParser::emptyMapFile();
    delete parser;
    return r;
}

map<string, string> FilmInfoHandler::createContext(Request* req) {
    map<string, string> context;
    context[FILM_ID] = req->getQueryParam("id");
    if (GET.hasFilm(req->getSessionId(), req->getQueryParam("id"))) 
        context["bought"] = "true";
    else {
        if (GET.canBuy(req->getSessionId(), req->getQueryParam("id")))
            context["can_buy"] = "true";
    }
    context[FILMS] = GET.getFilmInfo(req->getQueryParam("id"));
    context[SUMMARY] = Network::getInstance()->getFilm(stoi(req->getQueryParam("id")))->getSummary();
    context[COMMENTS] = GET.getComments(context[FILM_ID]);
    context["recomms"] = GET.getRecomms(req->getSessionId(), req->getQueryParam("id"));
    context["username"] = GET.getUsername(req->getSessionId());
    return context;
}

Response* CommentHandler::callback(Request* req) {
    Response* r;
    POST.commentOnFilm(req->getBodyParam("comment"), req->getSessionId(), req->getQueryParam("id"));
    r = Response::redirect("/filminfo?id=" + req->getQueryParam("id"));
    return r;
}

Response* RateHandler::callback(Request* req) {
    map<string, string> args = req->getParamsMap();
    POST.rateFilm(args, req->getSessionId());
    Response* r = Response::redirect("/filminfo?id=" + req->getBodyParam(FILM_ID));
    return r;
}