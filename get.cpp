#include "get.h"

using namespace std;

Get::Get() {
    functionMap[FOLLOWERS] =
        [this](Args args){ getFollowers(args); };
    functionMap[PUBLISHED] =
        [this](Args args){ getPublishedFilms(args); };
    functionMap[FILMS] =
        [this](Args args){ getFilms(args); };
    functionMap[PURCHASED] = 
        [this](Args args){ showPurchasedFilms(args); };
}

void Get::getFollowers(Args& args) {
    // network->getFollowers();
}

void Get::getPublishedFilms(Args& args) {
    SearchFilmsArgs publishedArgs = getSearchArgs(args);
    // network->getPublishedFilms();
}

void Get::getFilms(Args& args) {
    if (mapHasKey(args, FILM_ID)) {
        ;// isNumber(args.at(FILM_ID)) ?
        //     network->showFilmInfo() : throw BadRequest();
    }
    SearchFilmsArgs publishedArgs = getSearchArgs(args);
    // network-> searchFilm();
}

void Get::showPurchasedFilms(Args& args) {
    SearchFilmsArgs publishedArgs = getSearchArgs(args);
    // network->showPurchasedFilms();
}

SearchFilmsArgs Get::getSearchArgs(Args& args) {
    SearchFilmsArgs publishedArgs;
    if (mapHasKey(args, NAME))
        publishedArgs.name = args[NAME];
    if (mapHasKey(args, DIRECTOR))
        publishedArgs.director = args[DIRECTOR];
    if (mapHasKey(args, MIN_RATE))
        isNumber(args.at(MIN_RATE)) ?
            publishedArgs.minRate = stoi(args.at(MIN_RATE)) : throw BadRequest();
    if (mapHasKey(args, MAX_RATE))
        isNumber(args.at(MAX_RATE)) ?
            publishedArgs.maxRate = stoi(args.at(MAX_RATE)) : throw BadRequest();
    if (mapHasKey(args, MIN_YEAR))
        isNumber(args.at(MIN_YEAR)) ?
            publishedArgs.minYear = stoi(args.at(MIN_YEAR)) : throw BadRequest();
    if (mapHasKey(args, MAX_YEAR))
        isNumber(args.at(MAX_YEAR)) ?
            publishedArgs.maxYear = stoi(args.at(MAX_YEAR)) : throw BadRequest();
    if (mapHasKey(args, PRICE))
        isNumber(args.at(PRICE)) ?
            publishedArgs.price = stoi(args.at(PRICE)) : throw BadRequest();
    return publishedArgs;
}