#ifndef GET_H
#define GET_H

#include "request.h"

class Get : public Request {
public:
    Get();

private:
    void getFollowers(Args& args);
};

#endif