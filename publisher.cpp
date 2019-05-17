#include "publisher.h"

using namespace std;

Publisher::Publisher(SignupArgs args, int _id) 
    :User(args, _id) {}

void Publisher::addNewFilm(Film* film) {
    producedFilms.push_back(film);
    for (int i = 0; i < followers.size(); i++) {
        followers[i]->addNotif(PUBLISHE_NOTIF + username + 
            WITH_ID + to_string(id) + REGISTER_NEW_FILM);
    }
}

void Publisher::showFollowers() {
    cout << LIST_OF_FOLLOWERS << endl 
    <<  FOLLOWERS_LIST_HEADER << endl;
    for (int i = 0; i < followers.size(); i++) {
        cout << i + 1 << "." << followers[i] << endl;
    }
}

void Publisher::showFilms(SearchFilmsArgs args) {
    cout << GET_FILMS_HEADER << endl;
    int num = 1;
    for (int i = 0; i < producedFilms.size(); i++) {
        if (producedFilms[i]->isInFilter(args))
            cout << num++ << ". " << *(producedFilms[i]) << endl;
    }
}

void Publisher::addFollower(User* user) {
    for (int i = 0; i < followers.size(); i++) {
        if (user == followers[i])
            return;
    }
    followers.push_back(user);
    newNotifications.push_back(
        USER_NOTIF + user->getName() + 
        WITH_ID + to_string(user->getId()) + FOLLOW_YOU
    );
}