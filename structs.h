#ifndef STRUCTS_H
#define STRUCTS_H

#include <map>
#include <string>
#include "defines.h"

struct StructedInput {
    std::string method;
    std::string command;
    Args args;
};

struct SignupArgs {
    std::string email;
    std::string username;
    std::string password;
    int age;
    std::string publisher; 
};

struct LoginArgs {
    std::string username;
    std::string password;
};

struct NewFilmArgs {
    std::string name;
    std::string summary;
    std::string director;
    int year;
    int length;
    int price;
};

struct ReplyArgs {
    std::string content;
    int filmId;
    int commentId;
};

struct RateArgs {
    int score;
    int filmId;
};

struct CommentArgs {
    int filmId;
    std::string content;
};

struct EditFilmArgs {
    int filmId;
    std::string name;
    std::string summary;
    std::string director;
    int year;
    int length;
    int price;
    EditFilmArgs():
        year(NOT_STATED), 
        length(NOT_STATED),
        price(NOT_STATED) {}
};

struct SearchFilmsArgs {
    std::string name;
    std::string director;
    int minRate;
    int maxRate;
    int minYear;
    int maxYear;
    int price;
    SearchFilmsArgs():
        minYear(NOT_STATED),
        maxYear(NOT_STATED),
        minRate(NOT_STATED),
        maxRate(NOT_STATED),
        price(NOT_STATED) {}

};

struct DeleteCommentArgs {
    int filmId;
    int commentId;
};

#endif