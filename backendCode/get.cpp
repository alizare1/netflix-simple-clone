#include "get.h"

using namespace std;

bool Get::isPublisher(string sid) {
    return network->isPublisher(stoi(sid));
}

string Get::getUsername(string sid) {
    return network->getUsername(stoi(sid));
}

string Get::getPublishedFilms(string sid, string director) {
    return network->getPublishedFilms(stoi(sid), director);
}

SearchFilmsArgs Get::getSearchArgs(Args& args) {
    SearchFilmsArgs publishedArgs;
    if (args.count(NAME))
        publishedArgs.name = args[NAME];
    if (args.count(DIRECTOR))
        publishedArgs.director = args[DIRECTOR];
    if (args.count(MIN_RATE))
        isNumber(args.at(MIN_RATE)) ?
            publishedArgs.minRate = stoi(args.at(MIN_RATE)) : throw BadRequest();
    if (args.count(MAX_RATE))
        isNumber(args.at(MAX_RATE)) ?
            publishedArgs.maxRate = stoi(args.at(MAX_RATE)) : throw BadRequest();
    if (args.count(MIN_YEAR))
        isNumber(args.at(MIN_YEAR)) ?
            publishedArgs.minYear = stoi(args.at(MIN_YEAR)) : throw BadRequest();
    if (args.count(MAX_YEAR))
        isNumber(args.at(MAX_YEAR)) ?
            publishedArgs.maxYear = stoi(args.at(MAX_YEAR)) : throw BadRequest();
    if (args.count(PRICE))
        isNumber(args.at(PRICE)) ?
            publishedArgs.price = stoi(args.at(PRICE)) : throw BadRequest();
    return publishedArgs;
}

string Get::getAbleToBuyFilms(string sid) {
    return network->getAbleToBuyFilms(stoi(sid));
}

string Get::getBoughtMovies(string sid) {
    return network->getBoughtFilms(stoi(sid));
}

string Get::getFilmInfo(string filmId) {
    return network->getFilmInfo(stoi(filmId));
}

bool Get::canBuy(string sid, string filmId) {
    return network->canBuy(stoi(sid), stoi(filmId));
}

bool Get::hasFilm(string sid, string filmId) {
    return network->hasFilm(stoi(sid), stoi(filmId));
}

string Get::getComments(string filmId){
    return network->getComments(stoi(filmId));
}

string Get::getRecomms(string sid, string filmId) {
    return network->getRecomms(stoi(sid), stoi(filmId));
}