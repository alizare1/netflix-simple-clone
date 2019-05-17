#ifndef GET_H
#define GET_H

#include "request.h"

class Get : public Request {
public:
    Get(Network* _network);

private:
    void getFollowers(Args& args);
    void getPublishedFilms(Args& args);
    void getFilms(Args& args);
    void showPurchasedFilms(Args& args);
    SearchFilmsArgs getSearchArgs(Args& args);
};

#endif