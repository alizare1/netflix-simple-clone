#include "commandInterface.h"
#include "network.h"


int main() {
    Network* network = new Network();
    CommandInterface cm(network);
    cm.run();
    delete network;
}