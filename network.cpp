#include "network.h"

using namespace std;

Network::Network() {
    currUser = nullptr;
    currPub = nullptr;
    netWorkMoney = 0;
}

void Network::signup(SignupArgs& args) {
    if (usersByName.count(args.username))
        throw BadRequest();
    currPub = nullptr;
    currUser = nullptr;
    User* newUser;
    if (args.publisher) {
        Publisher* newPub = new Publisher(args, usersById.size() + 1);
        publishers[newPub->getId()] = newPub;
        newUser = newPub;
        currPub = newPub;
    }
    else
        newUser = new User(args, usersById.size() + 1);
    usersById[newUser->getId()] = newUser;
    usersByName[args.username] = newUser;
    currUser = newUser;
}

void Network::login(LoginArgs& args) {
    if (!usersByName.count(args.username))
        throw BadRequest();
    if (usersByName[args.username]->checkPassword(args.password)) {
        currUser = usersByName[args.username];
        if (currUser->isPublisher())
            currPub = publishers[currUser->getId()];
        else
            currPub = nullptr;
    }
    else 
        throw BadRequest();
}

void Network::addNewFilm(NewFilmArgs& args) {
    if (!isPublisherLoggedIn())
        throw PermissionDenied();
    Film* newFilm = new Film(args, films.size() + 1, currPub);
    films[newFilm->getId()] = newFilm;
    currPub->addNewFilm(newFilm);
    filmsByScore.push_back(newFilm);
}

void Network::editFilm(EditFilmArgs& args) {
    checkFilmOwnership(args.filmId);
    films[args.filmId]->editFilm(args);
}

void Network::deleteFilm(int filmId) {
    checkFilmOwnership(filmId);
    films[-filmId] = films[filmId];
    films.erase(filmId);
}

void Network::checkFilmOwnership(int filmId) {
    if (!isPublisherLoggedIn())
        throw PermissionDenied();
    if (!films.count(filmId))
        throw NotFound();
    if(films[filmId]->getPublisher() != currPub)
        throw PermissionDenied();
}

void Network::deleteComment(DeleteCommentArgs& args) {
    checkFilmOwnership(args.filmId);
    films[args.filmId]->deleteComment(args.commentId);
}

bool Network::isPublisherLoggedIn(){
    return currPub != nullptr;
}

void Network::showFollowers() {
    if (!isPublisherLoggedIn())
        throw PermissionDenied();
    currPub->showFollowers();
}

void Network::follow(int PubId) {
    if (!isLoggedIn())
        throw PermissionDenied();
    if (!publishers.count(PubId))
        throw NotFound();
    publishers[PubId]->addFollower(currUser);
}

void Network::addMoney(int amount) {
    if (!isLoggedIn())
        throw PermissionDenied();
    currUser->addMoney(amount);
}

void Network::withdrawMoney() {
    if (!isPublisherLoggedIn())
        throw PermissionDenied();
    currPub->addMoney(publishersMoney[currPub->getId()]);
    publishersMoney[currPub->getId()] = 0;
}

bool Network::isLoggedIn() {
    return currUser != nullptr;
}

void Network::getPublishedFilms(SearchFilmsArgs& args) {
    if (!isPublisherLoggedIn())
        throw PermissionDenied();
    currPub->showFilms(args);
}

void Network::replyToComment(ReplyArgs& args) {
    checkFilmOwnership(args.filmId);
    films[args.filmId]->replyToComment(args);
}

void Network::commentOnFilm(CommentArgs& args) {
    if (isLoggedIn())
        throw PermissionDenied();
    if (!films.count(args.filmId))
        throw NotFound();
    films[args.filmId]->comment(args.content, currUser);
    sendNotif(films[args.filmId], COMMENT_ON_FILM);
}

void Network::searchFilms(SearchFilmsArgs& args) {
    cout << GET_FILMS_HEADER << endl;
    std::map<int, Film*>::iterator it = films.begin();
    int counter = 1;
    while (it != films.end()) {
        if (it->second->isInFilter(args))
            cout << counter++ << ". " << *(it->second) << endl;
        it++;
    }
}

void Network::showPurchasedFilms(SearchFilmsArgs& args) {
    if (!isLoggedIn())
        throw PermissionDenied();
    currUser->showPurchasedFilms(args);
}

void Network::showFilmInfo(int filmId) {
    if (!isLoggedIn())
        throw PermissionDenied();
    if (!films.count(filmId)) 
        throw NotFound();
    films[filmId]->showFilmInfo();
    showRecomms();
}

void Network::showRecomms() {
    cout << RECOMMS_INFO << endl << RECOMMS_HEADER << endl;
    int count = 0;
    for (int i = 0; i < filmsByScore.size(); i++) {
        if (!currUser->hasFilm(filmsByScore[i])) {
            cout << i + 1 << ". ";
            filmsByScore[i]->showAsRecom();
            cout << endl;
            count++;
        }
        if (count == 4)
            return;
    }
}

void Network::inserFilmByScore(Film* film) {
    for (int i = 0; filmsByScore[i] != film; i++) {
        if (film->getAverageScore() > filmsByScore[i]->getAverageScore()) {
            filmsByScore.erase(find(filmsByScore.begin(), filmsByScore.end(), film));
            filmsByScore.insert(filmsByScore.begin() + i, film);
            return;
        }
    }
}

void Network::buyFilm(int filmId) {
    if (!isLoggedIn())
        throw PermissionDenied();
    if (!films.count(filmId))
        throw NotFound();
    currUser->buyFilm(films[filmId]);
    sendNotif(films[filmId], BUY_YOUR_FILM);
    calculatePublisherCut(films[filmId]);
}

void Network::sendNotif(Film* film, string action) {
    film->getPublisher()->addNotif (
            USER_NOTIF + currUser->getName() 
            + WITH_ID + to_string(currUser->getId()) + action
            + film->getName() + WITH_ID + 
            to_string(film->getId()) + "."
        );
}

void Network::calculatePublisherCut(Film* film) {
    float score = film->getAverageScore();
    int PubsCut;
    if (score < LOW_SCORE_MAX)
        PubsCut = LOW_SCORE_RATIO * film->getPrice();
    else if (score < AVERAGE_SCORE_MAX)
        PubsCut = AVERAGE_SCORE_RATIO * film->getPrice();
    else 
        PubsCut = HIGH_SCORE_RATIO * film->getPrice();
    publishersMoney[film->getPublisher()->getId()] += PubsCut;
    netWorkMoney += film->getPrice() - PubsCut;
}

void Network::rateFilm(RateArgs& args) {
    if (!isLoggedIn())
        throw PermissionDenied();
    if (!films.count(args.filmId))
        throw NotFound();
    films[args.filmId]->rate(args.score, currUser->getId());
    sendNotif(films[args.filmId], RATE_YOUR_FILM);
}

void Network::showNewNotifs() {
    if (!isLoggedIn())
        throw PermissionDenied();
    currUser->showNewNotifs();
}

void Network::showNotifs(int limit) {
    if (!isLoggedIn())
        throw PermissionDenied();
    currUser->showNotifs(limit);
}