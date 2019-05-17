#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "user.h"

class Publisher : public User {
public:
    Publisher(SignupArgs args, int _id);
    void addNewFilm();
    void showFollowers();
    void showMovies(SearchFilmsArgs args);
    
private:
    std::vector<Film*> producedFilms;
    std::vector<User*> followers;

};

#endif