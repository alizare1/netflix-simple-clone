#include "commandInterface.h"
#include "network.h"


int main() {
    CommandInterface cm(new Network);
    cm.run();
}