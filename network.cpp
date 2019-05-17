#include "network.h"

using namespace std;

void Network::signup(SignupArgs& args) {
    if (usersByName.count(args.username))
        throw BadRequest();
    User* newUser;
    if (args.publisher) {
        Publisher* newPub = new Publisher(args, users.size() + 1);
        publishers[newPub->getId()] = newPub;
        newUser = newPub;
        currPub = newPub;
    }
    else
        newUser = new User(args, usersById.size() + 1);
    usersById[newUser->getId()] = newUser;
    usersByName[args.username] = newUser;
    currUser = newUser;
}

