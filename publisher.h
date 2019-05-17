#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "user.h"
#include <string>
#include "film.h"
#include <iostream>
#include <vector>
#include "structs.h"
#include "defines.h"

class Film;
class User;

class Publisher : public User {
public:
    Publisher(SignupArgs args, int _id);
    void addNewFilm(Film* film);
    void showFollowers();
    void showFilms(SearchFilmsArgs args);
    void addFollower(User* user);
    
private:
    
    std::vector<Film*> producedFilms;
    std::vector<User*> followers;

};

#endif