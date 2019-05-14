#include "get.h"

using namespace std;

Get::Get() {
    functionMap[FOLLOWERS] =
        [this](Args args){ getFollowers(args); };
    functionMap[PUBLISHED] =
        [this](Args args){ getPublishedFilms(args); };
}

void Get::getFollowers(Args& args) {
    // if (args.size() > 2)
    //     throw BadRequest();

    // network->getFollowers();
}

void Get::getPublishedFilms(Args& args) {
    PublishedFilmsArgs publishedArgs = getPublishedArgs(args);
    // network->getPublishedFilms();
}

PublishedFilmsArgs Get::getPublishedArgs(Args& args) {
    PublishedFilmsArgs publishedArgs;
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