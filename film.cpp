#include "film.h"

using namespace std;

Film::Film(NewFilmArgs& args, int _id, Publisher* pub) {
    publisher = pub;
    director = args.director;
    year = args.year;
    summary = args.summary;
    name = args.name;
    length = args.length;
    price = args.price;
    id = _id;
    deleted = false;
}

Film::~Film() {
    for (int i = 0; i < comments.size(); i++)
        delete comments[i];
}

int Film::getId() {
    return id;
}

void Film::rate(int score, int userId) {
    if (score < 0 || score > 10)
        throw BadRequest();
    usersScore[userId] = score;
}

float Film::getAverageScore() {
    if (usersScore.size() == 0)
        return 0;
    std::map<int, int>::iterator it = usersScore.begin();
    float sum = 0;
    while (it != usersScore.end()) {
        sum += it->second;
        it++;
    }
    return sum / usersScore.size();
}

void Film::comment(string text, User* user) {
    Comment* cm = new Comment(text, user, comments.size() + 1, this);
    comments.push_back(cm);
}

Publisher* Film::getPublisher() {
    return publisher;
}

bool Film::isInFilter(SearchFilmsArgs args) {
    if (args.director != "")
        if (director != args.director)
            return false;
    if (args.name != "")
        if (name != args.name)
            return false;
    if (args.minYear != NOT_STATED) 
        if (year < args.minYear)
            return false;
    if (args.maxYear != NOT_STATED) 
        if (year > args.maxYear)
            return false;
    if (args.minRate != NOT_STATED) 
        if (getAverageScore() <= args.minRate)
            return false;
    if (args.maxRate != NOT_STATED) 
        if (getAverageScore() > args.maxRate)
            return false;
    if (args.price != NOT_STATED)
        if (price != args.price)
            return false;
    return true;
    
}

string Film::getFilmInfo() {
    stringstream ss;
    ss << "<td>" << "  <a style=\"color: #ddd\" href=\"filminfo?id=" << id << "\">" << name << "</a> </td>";
    ss << "<td>" << director << "</td>";
    ss << "<td>" << price << "</td>";
    ss << "<td>" << getAverageScore() << "</td>";
    ss << "<td>" << year << "</td>";
    ss << "<td>" << length << "</td>";
    return ss.str();
}

string Film::showFilmInfo() {
    stringstream ss;
    ss << "<h4>" << name <<  "<sub>" << year << "</sub></h4>";
    ss << "";
    ss << "        <p style=\"font-size: 10px\">";
    ss << "            <span>" << director << "</span>";
    ss << "            &nbsp;&nbsp;-&nbsp;&nbsp;";
    ss << "            <span>"<< length << "min</span>";
    ss << "            &nbsp;&nbsp;-&nbsp;&nbsp;";
    ss << "            <span>Rating: " << getAverageScore() << "/10</span>";
    ss << "            &nbsp;&nbsp;-&nbsp;&nbsp;";
    ss << "            <span>" << price << "$</span>";
    ss << "        </p>";
    return ss.str();
}

string Film::showAsRecom() {
    stringstream ss;
    ss << "<a href=\"filminfo?id=" << id << "\">" << name << "</a>" << "  " << length << "  " << director;
    return ss.str();
}

int Film::getPrice() {
    return price;
}

std::string Film::getName() {
    return name;
}

void Film::deleteFilm() {
    deleted = true;
}

bool Film::isDeleted() {
    return deleted;
}

string Film::getComments() {
    stringstream ss;
    for (int i = 0; i < comments.size(); i++) {
        ss << "<p>" << comments[i]->getContent() << "</p>";
    }
    return ss.str();
}

string Film::getSummary() {
    return summary;
}