#include "film.h"

using namespace std;

Film::Film(NewFilmArgs args, int _id) {
    director = args.director;
    year = args.year;
    summary = args.summary;
    name = args.name;
    length = args.length;
    price = args.price;
    id = _id;
}

void Film::rate(int score, int userId) {
    if (score < 0 || score > 10)
        throw BadRequest();
    usersScore[userId] = score;
}

float Film::getAverageScore() {
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
        throw BadRequest();
    if (comments[reply.commentId - 1] == nullptr)
        throw BadRequest();
    comments[reply.commentId - 1]->addReply(reply.content);
}

Publisher* Film::getPublisher() {
    return publisher;
}