#include "delete.h"

Delete::Delete() {
    functionMap[FILMS] =
        [this](Args args){ deleteFilm(args); };
    functionMap[COMMENTS] =
        [this](Args args){ deleteComment(args); };
}

void Delete::deleteFilm(Args& args) {
    if (mapHasKey(args, FILM_ID)) {
        ;// isNumber(args.at(FILM_ID)) ?
        //     network->deleteFilm() : throw BadRequest();
    }
    else
        throw BadRequest();
}

void Delete::deleteComment(Args& args) {
    DeleteCommentArgs commentArgs = getDeleteCommentArgs(args);
    // network->deleteComment();
}

DeleteCommentArgs Delete::getDeleteCommentArgs(Args& args) {
    DeleteCommentArgs commentArgs;
    try {
        isNumber(args.at(COMMENT_ID)) ?
            commentArgs.commentId = stoi(args.at(COMMENT_ID)) : throw BadRequest() ;
        isNumber(args.at(FILM_ID)) ?
            commentArgs.filmId = stoi(args.at(FILM_ID)) : throw BadRequest() ;
    }
    catch (std::exception& e) {
        throw BadRequest();
    }
    return commentArgs;
}