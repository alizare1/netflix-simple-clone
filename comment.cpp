#include "comment.h"

using namespace std;

Comment::Comment(string _content, User* _commenter, int _id, Film* _film) {
    film = _film;
    commenter = _commenter;
    id = _id;
    content = _content;
}

string Comment::getContent() {
    return content;
}
