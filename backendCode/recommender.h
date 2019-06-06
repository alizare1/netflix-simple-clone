#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include <vector>
#include "film.h"
#include "user.h"
#include <algorithm>
#include <iostream>

class Recommender {
public:
    void addFilm(Film* film);
    void updateMatrix(Film* film, User* user);
    void removeFilm(Film* film);
    std::vector<Film*> getSortedRecomList(Film* currFilm);


private:
    int getFilmIndex(Film* film);

    std::vector<Film*> films;
    std::vector<std::vector<int>> filmsMatrix;
};
#endif