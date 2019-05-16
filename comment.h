#ifndef COMMENT_H
#define COMMENT_H


#include <vector>
#include <string>
#include <iostream>
#include "user.h"

class User;

class Comment {
public:
    Comment(std::string _content, int _id);
    void addReply(std::string reply);
    void printComment();
private:
    int id;
    User* commenter;
    std::string content;
    std::vector<std::string> replies;
    friend std::ostream& operator<<(std::ostream& out, const Comment& c);
};

#endif