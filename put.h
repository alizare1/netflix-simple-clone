#ifndef PUT_H
#define PUT_H

#include "request.h"
#include <iostream>
#include "structs.h"
#include "exceptions.h"

class Put : public Request {
public:
    Put();
    void parseInput(StructedInput& structedInput);

private:
    void editFilm(Args& args);
    EditFilmArgs getFilmArgs(Args& args);

    std::map<std::string, std::function<void(Args)>> functionMap;
};

#endif