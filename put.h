#ifndef PUT_H
#define PUT_H

#include "request.h"
#include <iostream>
#include "structs.h"
#include "exceptions.h"

class Put : public Request {
public:
    Put();

private:
    void editFilm(Args& args);
    EditFilmArgs getFilmArgs(Args& args);

};

#endif