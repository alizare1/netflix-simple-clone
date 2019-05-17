#ifndef FILM_H
#define FILM_H

#include <string>
#include <vector>
#include <map>
#include "exceptions.h"
#include "publisher.h"
#include "comment.h"
#include "structs.h"

class Publisher;
class Comment;

class Film {
public:
    Film(NewFilmArgs& args, int _id, Publisher* pub);
    int getId();
    void rate(int score, int userId);
    float getAverageScore();
    void comment(std::string text, User* user);
    void replyToComment(ReplyArgs reply);
    Publisher* getPublisher();
    bool isInFilter(SearchFilmsArgs args);
    friend std::ostream& operator<<(std::ostream& out, Film& film);

private:

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