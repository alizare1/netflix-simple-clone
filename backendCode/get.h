#ifndef GET_H
#define GET_H

#include "myReq.h"

class Get : public MyRequest {
public:
    std::string getPublishedFilms(std::string sid, std::string director);
    void getFilms(Args& args);
    void showPurchasedFilms(Args& args);
    bool isPublisher(std::string sid);
    std::string getUsername(std::string sid);
    SearchFilmsArgs getSearchArgs(Args& args);
    std::string getAbleToBuyFilms(std::string sid);
    std::string getBoughtMovies(std::string sid);
    bool canBuy(std::string sid, std::string filmId);
    bool hasFilm(std::string sid, std::string filmId);
    std::string getFilmInfo(std::string filmId);
    std::string getComments(std::string filmId);
    std::string getRecomms(std::string sid, std::string filmId);

};

#endif