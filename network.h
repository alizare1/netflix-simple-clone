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

class Film;

class Network {
public:
    Network();
    void signup(SignupArgs& args);
    void login(LoginArgs& args);
    void addNewFilm(NewFilmArgs& args);
    void editFilm(EditFilmArgs& args);
    void deleteFilm(int filmId);
    void deleteComment(DeleteCommentArgs& args);
    void showFollowers();
    void withdrawMoney();
    void addMoney(int amount);
    void getPublishedFilms(SearchFilmsArgs& args);
    void replyToComment(ReplyArgs& args);
    void follow(int pubId);
    void searchFilms(SearchFilmsArgs& args);
    void showFilmInfo(int filmId);
    void buyFilm(int filmId);
    void rateFilm(RateArgs& args);
    void commentOnFilm(CommentArgs& args);
    void showPurchasedFilms(SearchFilmsArgs& args);
    void showNewNotifs();
    void showNotifs(int limit);



private:
    void checkFilmOwnership(int filmId);
    bool isPublisherLoggedIn();
    bool isLoggedIn();
    void sendNotif(Film* film, std::string action);
    void calculatePublisherCut(Film* film);
    void showRecomms(Film* currFilm);
    void inserFilmByScore(Film* film);

    int netWorkMoney;
    User* currUser;
    Publisher* currPub;
    std::map<int, Film*> films;
    std::vector<Film*> filmsByScore;
    std::map<int, User*> usersById;
    std::map<std::string, User*> usersByName;
    std::map<int, Publisher*> publishers;
    std::map<int, int> publishersMoney;

};


#endif