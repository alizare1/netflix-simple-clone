#include "comment.h"

using namespace std;

Comment::Comment(string _content, User* _commenter, int _id, Film* _film) {
    film = _film;
    commenter = _commenter;
    id = _id;
    content = _content;
}

void Comment::addReply(string reply) {
    replies.push_back(reply);
    commenter->addNotif(PUBLISHE_NOTIF + film->getPublisher()->getName()
        + WITH_ID + to_string(film->getPublisher()->getId()) + REPLY_TO_COMMENT);
}

void Comment::printComment() {
    cout << id << ". " << content << endl;
    for (int i = 0; i < replies.size(); i++) 
        cout << id << '.' << i + 1 << ". "  << replies[i] << endl;
}

ostream& operator<<(ostream& out, const Comment& c) {
    out << c.id << "." << c.content << endl;
    for (int i = 0; i < c.replies.size(); i++) {
        out << c.id << "." << i + 1 << "." 
            << c.replies[i] << endl;
    }
    return out;
}
