#include "user.h"

using namespace std;

User::User(SignupArgs args, int _id) {
    username = args.username;
    password = args.password;
    email = args.email;
    age = args.age;
    id = _id;
    isPub = args.publisher;
    money = 0;
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

std::string User::getName() {
    return username;
}

void User::buyFilm(Film* film) {
    if (film->getPrice() > money)
        throw PermissionDenied();
    money -= film->getPrice();
    for (int i = 0; i < boughtFilms.size(); i++) {
        if (film->getId() < boughtFilms[i]->getId()) {
            boughtFilms.insert(boughtFilms.begin() + i, film);
            return;
        }
    }
    boughtFilms.push_back(film);
}

bool User::hasFilm(Film* film) {
    for (int i = 0; i < boughtFilms.size(); i++) {
        if (boughtFilms[i] == film)
            return true;
    }
    return false;
}

void User::substractMoney(int amount) {
    money -= amount;
}

int User::getMoney() {
    return money;
}

string User::getBoughtFilms() {
    stringstream ss;
    for (int i = 0 ; i < boughtFilms.size(); i++) {
        ss << "<tr>" ;
        ss << "<th scope=\"row\">" << i + 1 << "</th>";
        ss << boughtFilms[i]->getFilmInfo(); 
        ss << "<tr>";
    }

    return ss.str();
}