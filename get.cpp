#include "get.h"

using namespace std;

Get::Get() {
    functionMap[FOLLOWERS] =
        [this](Args args){ getFollowers(args); };
}

void Get::getFollowers(Args& args) {
    // if (args.size() > 2)
    //     throw BadRequest();

    // network->getFollowers();
}