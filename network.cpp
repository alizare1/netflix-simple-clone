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
    if (currUser == nullptr)
        throw PermissionDenied();
    if (!publishers.count(PubId))
        throw NotFound();
    publishers[PubId]->addFollower(currUser);
}