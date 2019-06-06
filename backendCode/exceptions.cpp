#include "exceptions.h"

const char * NotFound::what() const throw () {
    return NOT_FOUND;
}

const char * BadRequest::what() const throw () {
    return BAD_REQUEST;
}

const char * PermissionDenied::what() const throw () {
    return PERM_DENIED;
}