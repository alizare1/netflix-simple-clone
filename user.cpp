#include "user.h"

using namespace std;

User::User(SignupArgs args, int _id) {
    username = args.username;
    password = args.password;
    email = args.email;
    age = args.age;
    id = _id;
    isPub = args.publisher;
}

bool User::checkPassword(string pw) {
    if (pw == password)
        return true;
    return false;
}

int User::getId() {
    return id;
}

void User::addMoney(int amount) {
    money += amount;
}

bool User::isPublisher() {
    return isPub;
}

void User::addNotif(string notif) {
    newNotifications.push_back(notif);
}

void User::showNotifs(int limit) {
    int lastIndex = notifications.size() - 1;
    for (int i = lastIndex; i > lastIndex - limit; i--) {
        cout << notifications[i] << endl;
    }
}

void User::showNewNotifs() {
    int lastIndex = newNotifications.size() - 1;
    for (int i = lastIndex; i >= 0; i--)
        cout << newNotifications[i] << endl;
    for (int i = 0; i <= lastIndex; i++) {
        notifications.push_back(newNotifications[i]);
        newNotifications.erase(newNotifications.begin() + i);
    }
}

std::string User::getName() {
    return username;
}

ostream& operator<<(ostream& out, User& user) {
    out << user.id  << " | " << user.username 
        << " | " << user.email;
    return out;
}

void User::showPurchasedFilms(SearchFilmsArgs& args) {
    cout << GET_FILMS_HEADER << endl;
    for (int i = 0; i < boughtFilms.size(); i++) {
        if (boughtFilms[i]->isInFilter(args))
            cout << boughtFilms[i] << endl;
    }
}