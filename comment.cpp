#include "comment.h"

using namespace std;

Comment::Comment(string _content, int _id) {
    id = _id;
    content = _content;
}

void Comment::addReply(string reply) {
    replies.push_back(reply);
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
