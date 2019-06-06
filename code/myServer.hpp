#ifndef MY_SERVER_H
#define MY_SERVER_H

#include "../server/server.hpp"
#include "../backendCode/network.h"

class MyServer : public Server {
public:
    MyServer(int port = 5000);
    ~MyServer();
private:
    Network* network;
};

#endif