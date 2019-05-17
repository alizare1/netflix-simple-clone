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

class Film;

class Network {
public:
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

    User* currUser;
    Publisher* currPub;
    std::map<int, Film*> films;
    std::map<int, User*> usersById;
    std::map<std::string, User*> usersByName;
    std::map<int, Publisher*> publishers;
    std::map<int, int> publishersMoney;
    std::array<Film*, 4> top4;
    std::vector<std::string> takenNames;

};


#endif