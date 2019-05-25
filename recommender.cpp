#include "recommender.h"

using namespace std;

void Recommender::addFilm(Film*  film) {
    films.push_back(film);
    filmsMatrix.push_back(vector<int>());
    for (int i = 0 ; i < filmsMatrix.size(); i++) {
        filmsMatrix[filmsMatrix.size() - 1].push_back(0);
        if (i == filmsMatrix.size() - 1)
            break;
        filmsMatrix[i].push_back(0);
    }
}

void Recommender::updateMatrix(Film* film, User* user) {
    int filmIndex = getFilmIndex(film);
    for (int i = 0; i < films.size(); i++) {
        if (i == filmIndex)
            continue;
        if (user->hasFilm(films[i])) {
            filmsMatrix[filmIndex][i] += 1; 
            filmsMatrix[i][filmIndex] += 1;
        }
    }
}

void Recommender::removeFilm(Film* film) {
    int filmIndex = getFilmIndex(film);
    filmsMatrix.erase(filmsMatrix.begin() + filmIndex);
    for (int i = 0; i < filmsMatrix.size(); i++) {
        filmsMatrix[i].erase(filmsMatrix[i].begin() + filmIndex);
    }
    films.erase(films.begin() + filmIndex);
}

vector<Film*> Recommender::getSortedRecomList(Film* currFilm) {
    vector<Film*> sortedList;
    int filmIndex = getFilmIndex(currFilm);
    vector<int> sortedWeights = filmsMatrix[filmIndex];
    sort(sortedWeights.begin(), sortedWeights.end());

    for (int i = sortedWeights.size() - 1; i >= 0; i--) {

        for (int j = 0; j < filmsMatrix[filmIndex].size(); j++) {

            if (filmsMatrix[filmIndex][j] == sortedWeights[i]) {

                if (find(sortedList.begin(), sortedList.end(), films[j]) == sortedList.end())
                    sortedList.push_back(films[j]);

            }

        }

    }
    
    return sortedList;
}

int Recommender::getFilmIndex(Film* film) {
    return distance(films.begin(), find(films.begin(), films.end(), film));
}
