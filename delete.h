#ifndef DELETE_H
#define DELELE_H

#include "request.h"

class Delete : public Request {
public:
    Delete(Network* _network);

private:
    void deleteFilm(Args& args);
    void deleteComment(Args& args);
    DeleteCommentArgs getDeleteCommentArgs(Args& args);
};

#endif