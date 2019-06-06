#include "network.h"

using namespace std;

Network* Network::instance = 0;

Network* Network::getInstance() {
    if (instance == 0)
        instance = new Network();
    return instance;
}

Network::Network() {
    setAdmin();
}

Network::~Network() {
    map<int, Film*>::iterator it;
    for (it = films.begin(); it != films.end(); it++)
        delete it->second;
    map<int, User*>::iterator userIt;
    for (userIt = usersById.begin(); userIt != usersById.end(); userIt++)
        delete userIt->second;
}

void Network::setAdmin() {
    SignupArgs adminArgs;
    adminArgs.age = 0;
    adminArgs.email = ADMIN_MAIL;
    adminArgs.password = ADMIN_PW;
    adminArgs.publisher = false;
    adminArgs.username = ADMIN;
    admin = new User(adminArgs, 1);
    usersById[1] = admin;
    usersByName[ADMIN] = admin;
}

int Network::signup(SignupArgs& args) {
    if (usersByName.count(args.username))
        throw BadRequest();
    User* newUser;
    if (args.publisher) {
        Publisher* newPub = new Publisher(args, usersById.size() + 1);
        publishers[newPub->getId()] = newPub;
        newUser = newPub;
    }
    else
        newUser = new User(args, usersById.size() + 1);
    usersById[newUser->getId()] = newUser;
    usersByName[args.username] = newUser;

    return newUser->getId();
}

int Network::login(LoginArgs& args) {
    if (!usersByName.count(args.username))
        throw BadRequest();
    return usersByName[args.username]->getId();
}

void Network::addNewFilm(NewFilmArgs& args, int sid) {
    Film* newFilm = new Film(args, films.size() + 1, publishers[sid]);
    films[newFilm->getId()] = newFilm;
    publishers[sid]->addNewFilm(newFilm);
    filmsByScore.push_back(newFilm);
    recommender.addFilm(newFilm);
}

void Network::deleteFilm(int filmId, int sid) {
    checkFilmOwnership(filmId, sid);
    films[filmId]->deleteFilm();
    films[-filmId] = films[filmId];
    filmsByScore.erase(find(filmsByScore.begin(), 
        filmsByScore.end(), films[filmId]));
    recommender.removeFilm(films[filmId]);
    films.erase(filmId);
}

void Network::deleteFilm(int filmId) {
    checkFilmOwnership(filmId);
    films[filmId]->deleteFilm();
    films[-filmId] = films[filmId];
    filmsByScore.erase(find(filmsByScore.begin(), 
        filmsByScore.end(), films[filmId]));
    recommender.removeFilm(films[filmId]);
    films.erase(filmId);
}

void Network::checkFilmOwnership(int filmId, int sid) {
    if (!isPublisher(sid))
        throw PermissionDenied();
    if (!films.count(filmId))
        throw NotFound();
    if(films[filmId]->getPublisher() != publishers[sid])
        throw PermissionDenied();
}

void Network::addMoney(int sid, int amount) {
    usersById[sid]->addMoney(amount);
}

void Network::commentOnFilm(string content, int sid, int filmId) {
    films[filmId]->comment(content, usersById[sid]);
}

void Network::showFilmInfo(int filmId) {
    if (!isLoggedIn())
        throw PermissionDenied();
    if (!films.count(filmId)) 
        throw NotFound();
    films[filmId]->showFilmInfo();
    showRecomms(films[filmId]);
}

void Network::showRecomms(Film* currFilm) {
    cout << RECOMMS_INFO << endl << RECOMMS_HEADER << endl;
    int count = 0;
    vector<Film*> sortedRecomList = recommender.getSortedRecomList(currFilm);
    for (int i = 0; i < sortedRecomList.size(); i++) {
        if (sortedRecomList[i] == currFilm)
            continue;
        if (currUser->hasFilm(sortedRecomList[i])) 
            continue;
        cout << ++count << ". ";
        sortedRecomList[i]->showAsRecom();
        cout << endl;
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

void Network::buyFilm(int sid, int filmId) {
    usersById[sid]->buyFilm(films[filmId]);
    calculatePublisherCut(films[filmId]);
    recommender.updateMatrix(films[filmId], usersById[sid]);
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
    admin->addMoney(film->getPrice());
}

void Network::rateFilm(RateArgs& args, int sid) {
    films[args.filmId]->rate(args.score, sid);
}

bool Network::isPublisher(int sid) {
    if (publishers.count(sid))
        return true;
    return false;
}
