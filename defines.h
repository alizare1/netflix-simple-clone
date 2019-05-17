#ifndef DEFINES_H
#define DEFINES_H

#define QUESTION_MARK "?"
#define POST_STR "POST"
#define GET_STR "GET"
#define PUT_STR "PUT"
#define DELETE_STR "DELETE"

#define LOGIN "login"
#define SIGNUP "signup"
#define FILMS "films"
#define MONEY "money"
#define RELPIES "replies"
#define FOLLOWERS "followers"
#define BUY "buy"
#define RATE "rate"
#define COMMENTS "comments"
#define PUBLISHED "published"
#define PURCHASED "purchased"

#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define AGE "age"
#define PUBLISHER "publisher"
#define SUMMARY "summary"
#define NAME "name"
#define YEAR "year"
#define LENGTH "length"
#define PRICE "price"
#define DIRECTOR "director"
#define AMOUNT "amount"
#define FILM_ID "film_id"
#define COMMENT_ID "comment_id"
#define CONTENT "content"
#define USER_ID "user_id"
#define SCORE "score"
#define MIN_RATE "min_rate"
#define MIN_YEAR "min_year"
#define MAX_RATE "max_rate"
#define MAX_YEAR "max_year"

#define TRUE "true"
#define FALSE "false"

#define USER "user"

#define NOT_STATED -1

#define WITH_ID " with id "
#define FOLLOW_YOU " follow you."
#define REPLY_TO_COMMENT " reply to your comment."
#define REGISTER_NEW_FILM " register new film."
#define BUY_YOUR_FILM " buy your film "
#define RATE_YOUR_FILM " rate your film "
#define COMMENT_ON_FILM " comment on your film "

#define LIST_OF_FOLLOWERS "List of Followers"
#define FOLLOWERS_LIST_HEADER "#. User Id  | User Username | User Email"
#define GET_FILMS_HEADER "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director"

#define SHOW_DETAILS_OF_FILM "Details of Film "
#define ID "Id = "
#define DIRECTOR_INFO "Director = "
#define LENGTH_INFO "Length = "
#define YEAR_INFO "Year = "
#define SUMMARY_INFO "Summary = "
#define RATE_INFO "Rate = "
#define PRICE_INFO "Price = "
#define COMMENTS_INFO "Comments"
#define RECOMMS_INFO "Recommendation Film"
#define RECOMMS_HEADER "#. Film Id | Film Name | Film Length | Film Director"

typedef std::map<std::string, std::string> Args;

#endif