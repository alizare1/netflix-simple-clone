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
    std::string getName();
    void showPurchasedFilms(SearchFilmsArgs& args);
    void buyFilm(Film* film);
    bool hasFilm(Film* film);
    int getMoney();
    void substractMoney(int amount);
    std::string getBoughtFilms();

protected:
    std::string username;
    std::string password;
    std::string email;
    int age;
    int id;
    int money;
    std::vector<Film*> boughtFilms;
    bool isPub;


};

#include "film.h"
#endif