#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

#define BAD_REQUEST "Bad Request\n"
#define NOT_FOUND "Not Found\n"
#define PERM_DENIED "Permission Denied\n"

class BadRequest : public std::exception {
public:
    const char * what() const throw ();
};

class NotFound : public std::exception {
public:
    const char * what() const throw ();
};

class PermissionDenied : public std::exception {
public:
    const char * what() const throw ();
};
#endif