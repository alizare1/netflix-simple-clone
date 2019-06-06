#ifndef FILM_H
#define FILM_H

#include <string>
#include <vector>
#include <map>
#include "exceptions.h"
#include "publisher.h"
#include "comment.h"
#include "structs.h"
#include <sstream>

class Publisher;
class Comment;

class Film {
public:
    Film(NewFilmArgs& args, int _id, Publisher* pub);
    ~Film();
    int getId();
    int getPrice();
    std::string getName();
    void rate(int score, int userId);
    float getAverageScore();
    void comment(std::string text, User* user);
    Publisher* getPublisher();
    bool isInFilter(SearchFilmsArgs args);
    std::string showFilmInfo();
    std::string showAsRecom();
    void deleteFilm();
    bool isDeleted();
    std::string getFilmInfo();
    std::string getComments();
    std::string getSummary();

private:

    bool deleted;
    std::string name;
    std::string summary;
    std::string director;
    int id;
    int year;
    int length;
    int price;
    Publisher* publisher;
    std::vector<Comment*> comments;
    std::map<int, int> usersScore;
    

};

#endif