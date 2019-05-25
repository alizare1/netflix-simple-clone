#ifndef USER_H
#define USER_H


#include <vector>
#include <string>
#include "structs.h"
#include <iostream>

class Film;

class User {
public:
    User(SignupArgs args, int _id);
    bool checkPassword(std::string pw);
    int getId();
    void addMoney(int amount);
    bool isPublisher();
    void addNotif(std::string notif);
    void showNotifs(int limit);
    void showNewNotifs();
    std::string getName();
    void showPurchasedFilms(SearchFilmsArgs& args);
    void buyFilm(Film* film);
    bool hasFilm(Film* film);
    friend std::ostream& operator<<(std::ostream& out, User& user);
    void showMoney();
    void substractMoney(int amount);

protected:
    std::string username;
    std::string password;
    std::string email;
    int age;
    int id;
    int money;
    std::vector<std::string> newNotifications;
    std::vector<std::string> notifications;
    std::vector<Film*> boughtFilms;
    bool isPub;


};

#include "film.h"
#endif