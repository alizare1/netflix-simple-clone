#include "put.h"

using namespace std;

Put::Put(Network* _network)
    :Request(_network) {
    functionMap[FILMS] =
        [this](Args args){ editFilm(args); };
}

void Put::editFilm(Args& args) {
    EditFilmArgs filmArgs = getFilmArgs(args);
    network->editFilm(filmArgs);
}

EditFilmArgs Put::getFilmArgs(Args& args) {
    EditFilmArgs filmArgs;
    try {
        isNumber(args.at(FILM_ID)) ?
            filmArgs.filmId = stoi(args.at(FILM_ID)) : throw BadRequest();
    }
    catch(exception& e) {
        throw BadRequest();
    }
    if (mapHasKey(args, NAME)) 
        filmArgs.name = args[NAME];
    if (mapHasKey(args, SUMMARY))
        filmArgs.summary = args[SUMMARY];
    if (mapHasKey(args, DIRECTOR)) 
        filmArgs.director = args[DIRECTOR];
    if (mapHasKey(args, YEAR))
        isNumber(args.at(YEAR)) ?
            filmArgs.year = stoi(args.at(YEAR)) : throw BadRequest();
    if (mapHasKey(args, LENGTH))
        isNumber(args.at(LENGTH)) ?
            filmArgs.length = stoi(args.at(LENGTH)) : throw BadRequest();
    if (mapHasKey(args, PRICE))
        isNumber(args.at(PRICE)) ?
            filmArgs.price = stoi(args.at(PRICE)) : throw BadRequest();
    return filmArgs;
}