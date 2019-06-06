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
    std::string getContent();
private:
    int id;
    Film* film;
    User* commenter;
    std::string content;
};

#endif