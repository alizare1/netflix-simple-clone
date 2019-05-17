#include "network.h"

using namespace std;

void Network::signup(SignupArgs& args) {
    if (isNameTaken(args.username))
        throw BadRequest();
    User* newUser;
    if (args.publisher) {
        Publisher* newPub = new Publisher(args, users.size() + 1);
        publishers[newPub->getId()] = newPub;
        newUser = newPub;
        currPub = newPub;
    }
    else
        newUser = new User(args, users.size() + 1);
    users[newUser->getId()] = newUser;
    currUser = newUser;
}

bool Network::isNameTaken(string& name) {
    for (int i = 0; i < takenNames.size(); i++) {
        if (name == takenNames[i])
            return true;
    }
    return false;
}