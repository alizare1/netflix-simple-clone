#ifndef COMMENT_H
#define COMMENT_H


#include <vector>
#include <string>
#include <iostream>
#include "user.h"
#include "film.h"

class User;
class Film;

class Comment {
public:
    Comment(std::string _content, User* _commenter, int _id, Film*);
    void addReply(std::string reply);
    void printComment();
private:
    int id;
    Film* film;
    User* commenter;
    std::string content;
    std::vector<std::string> replies;
    friend std::ostream& operator<<(std::ostream& out, const Comment& c);
};

#endif