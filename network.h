#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>
#include <array>
#include <map>
#include "film.h"
#include "user.h"
#include "publisher.h"
#include "structs.h"
#include "defines.h"
#include "exceptions.h"
#include <algorithm>
#include "recommender.h"
#include <sstream>

class Film;

class Network {
public:
    static Network* getInstance();
    ~Network();
    int signup(SignupArgs& args);
    int login(LoginArgs& args);
    void addNewFilm(NewFilmArgs& args, int sid);
    void deleteFilm(int filmId, int sid);
    void addMoney(int sid, int amount);
    void getPublishedFilms(SearchFilmsArgs& args);
    void searchFilms(SearchFilmsArgs& args);
    void showFilmInfo(int filmId);
    void buyFilm(int sid, int filmId);
    void rateFilm(RateArgs& args, int sid);
    void showPurchasedFilms(SearchFilmsArgs& args);
    bool isPublisher(int sid);
    std::string getUsername(int sid);
    std::string getPublishedFilms(int sid, std::string director);
    std::string getAbleToBuyFilms(int sid);
    std::string getBoughtFilms(int sid);
    std::string getFilmInfo(int filmId);
    bool canBuy(int sid, int filmId);
    bool hasFilm(int sid, int filmId);
    std::string getComments(int filmId);
    void commentOnFilm(std::string content, int sid, int filmId);
    std::string getRecomms(int sid, int filmId);
    Film* getFilm(int filmId);
    int getMoney(int sid);

private:
    Network();
    void checkFilmOwnership(int filmId , int sid);
    bool isPublisherLoggedIn();
    bool isLoggedIn();
    void calculatePublisherCut(Film* film);
    void inserFilmByScore(Film* film);
    void setAdmin();

    static Network* instance;
    Recommender recommender;
    User* admin;
    std::map<int, Film*> films;
    std::vector<Film*> filmsByScore;
    std::map<int, User*> usersById;
    std::map<std::string, User*> usersByName;
    std::map<int, Publisher*> publishers;
    std::map<int, int> publishersMoney;

};


#endif