#include "network.h"

using namespace std;

Network::Network() {
    top4 = {nullptr};
    currUser = nullptr;
    currPub = nullptr;
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
    for (int i = 0; i < 4; i++) {
        if (top4[i] == nullptr) {
            top4[i] = newFilm;
            break;
        }
    }
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
}

void Network::searchFilms(SearchFilmsArgs& args) {
    std::map<int, Film*>::iterator it = films.begin();
    while (it != films.end()) {
        if (it->second->isInFilter(args))
            cout << it->second << endl;
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
    cout << RECOMMS_INFO << endl;
    for (int i = 0; i < 4; i++) {
        if (top4[i] == nullptr)
            break;
        cout << RECOMMS_HEADER << endl
            << i + 1 << ". ";
        top4[i]->showAsRecom();
        cout << endl; 
    }
}

void Network::buyFilm(int filmId) {
    if (!isLoggedIn())
        throw PermissionDenied();
    if (!films.count(filmId))
        throw NotFound();
    currUser->buyFilm(films[filmId]);
    sendBuyNotif(films[filmId]);
    calculatePublisherCut(films[filmId]);
}

void Network::sendBuyNotif(Film* film) {
    film->getPublisher()->addNotif (
            USER_NOTIF + currUser->getName() 
            + WITH_ID + to_string(currUser->getId()) + BUY_YOUR_FILM
            + film->getName() + WITH_ID + 
            to_string(film->getId()) + "."
        );
}

void Network::calculatePublisherCut(Film* film) {
    float score = film->getAverageScore();
    int PubsCut;
    if (score < 5)
        PubsCut = 8.0/10 * film->getPrice();
    else if (score < 8)
        PubsCut = 9.0/10 * film->getPrice();
    else 
        PubsCut = 9.5/10 * film->getPrice();
    publishersMoney[film->getPublisher()->getId()] += PubsCut;
}
