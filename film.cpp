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

void Film::replyToComment(ReplyArgs reply) {
    if (reply.commentId > comments.size())
        throw NotFound();
    if (comments[reply.commentId - 1] == nullptr)
        throw NotFound();
    comments[reply.commentId - 1]->addReply(reply.content);
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

ostream& operator<<(ostream& out, Film& film) {
    out << film.id << " | " << film.name << " | "
        << film.length << " | " << film.price << " | "
        << film.getAverageScore() << " | " << film.year
        << " | " << film.director;
    return out;
}

void Film::editFilm(EditFilmArgs& args) {
    if (args.director != "")
        director = args.director;
    if (args.name != "")
        name = args.name;
    if (args.summary != "")
        summary = args.summary;
    if (args.year != NOT_STATED) 
        year = args.year;
    if (args.price != NOT_STATED)
        price = args.price;
    if (args.length != NOT_STATED)
        length = args.length;
}

void Film::deleteComment(int cmId) {
    if (cmId > comments.size() || cmId < 1)
        throw NotFound();
    if (comments[cmId] == nullptr)
        throw NotFound();
    delete comments[cmId - 1];
    comments[cmId - 1] = nullptr;
}

void Film::showFilmInfo() {
    cout << SHOW_DETAILS_OF_FILM << name << endl
        << ID << id << endl << DIRECTOR_INFO << director 
        << endl << LENGTH_INFO << length << endl
        << YEAR_INFO << year << endl << SUMMARY_INFO
        << summary << endl << RATE_INFO << getAverageScore()
        << endl << PRICE_INFO << price << endl;
    cout << endl << COMMENTS_INFO << endl;
    for (int i = 0; i < comments.size(); i++)
        if (comments[i] != nullptr)
            cout << *comments[i] << endl;
}

void Film::showAsRecom() {
    cout << id << " | " << name << " | " << length << " | " << director;
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