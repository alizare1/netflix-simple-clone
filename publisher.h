#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "user.h"
#include <string>
#include "film.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "structs.h"
#include "defines.h"

class Film;
class User;

class Publisher : public User {
public:
    Publisher(SignupArgs args, int _id);
    void addNewFilm(Film* film);
    std::string getFilms(std::string director);
    
private:
    
    std::vector<Film*> producedFilms;

};

#endif