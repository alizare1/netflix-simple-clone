#ifndef FILM_H
#define FILM_H

#include <string>
#include <vector>
#include <map>
#include "exceptions.h"
#include "publisher.h"
#include "comment.h"
#include "structs.h"

class Film {
public:
    Film(NewFilmArgs args, int _id);
    void rate(int score, int userId);
    float getAverageScore();
    void comment(std::string text);
    void replyToComment(ReplyArgs reply);

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