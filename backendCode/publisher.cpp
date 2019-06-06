#include "publisher.h"

using namespace std;

Publisher::Publisher(SignupArgs args, int _id) 
    :User(args, _id) {}

void Publisher::addNewFilm(Film* film) {
    producedFilms.push_back(film);
}

string Publisher::getFilms(string director) {
    stringstream s;
    SearchFilmsArgs args;
    int count = 0;
    for (int i = 0; i < producedFilms.size(); i++) {
        args.director = director;
        if (producedFilms[i]->isDeleted() || !producedFilms[i]->isInFilter(args))
            continue;
        s << "<tr>" ;
        s << "<th scope=\"row\">" << ++count << "</th>";
        s << producedFilms[i]->getFilmInfo();
        s << "<td>" << "<a style=\"color: #ddd\" href=\"/deletefilm?id=" << producedFilms[i]->getId() << "\"> Delete </a> </td>";
        s << "</tr>";
    }
    return s.str();
}