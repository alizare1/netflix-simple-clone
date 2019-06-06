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

string Network::getUsername(int sid) {
    return usersById[sid]->getName();
}

string Network::getPublishedFilms(int sid, string director) {
    return publishers[sid]->getFilms(director);
}

string Network::getAbleToBuyFilms(int sid) {
    stringstream ss;
    string tableTagsAndStuff;
    map<int, Film*>::iterator it = films.begin();
    int count = 0;

    for (it ; it != films.end(); it++) {
        if (usersById[sid]->getMoney() >= it->second->getPrice()) {
            if (usersById[sid]->hasFilm(it->second))
                continue;
            ss << "<tr>" ;
            ss << "<th scope=\"row\">" << ++count << "</th>";
            ss << it->second->getFilmInfo();
            ss << "<td>" << "<a style=\"color: #ddd\" href=\"/buy?id=" << it->first << "\"> Buy </a> </td>";
            ss << "</tr>";
        }

    }

    return ss.str();
}

string Network::getBoughtFilms(int sid) {
    return usersById[sid]->getBoughtFilms();
}

string Network::getFilmInfo(int filmId) {
    return films[filmId]->showFilmInfo();
}

bool Network::canBuy(int sid, int filmId) {
    if (usersById[sid]->getMoney() >= films[filmId]->getPrice())
        return true;
    return false;
}

bool Network::hasFilm(int sid, int filmId) {
    if (usersById[sid]->hasFilm(films[filmId]))
        return true;
    return false;
}

string Network::getComments(int filmId) {
    return films[filmId]->getComments();
}

string Network::getRecomms(int sid, int filmId) {
    int count = 0;
    stringstream ss;
    vector<Film*> sortedRecomList = recommender.getSortedRecomList(films[filmId]);
    for (int i = 0; i < sortedRecomList.size(); i++) {
        if (sortedRecomList[i] == films[filmId])
            continue;
        if (usersById[sid]->hasFilm(sortedRecomList[i])) 
            continue;
        ss << "<a href=\"filminfo?id=" << sortedRecomList[i]->getId() << "\">";
        ss << ++count << ". ";
        ss << sortedRecomList[i]->getName();
        ss << "</a> <br>";
        if (count == 4)
            return ss.str();
    }
    return ss.str();
}

Film* Network::getFilm(int filmId) {
    return films[filmId];
}

int Network::getMoney(int sid) {
    return usersById[sid]->getMoney();
}
