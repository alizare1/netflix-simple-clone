#include "myServer.hpp"

MyServer::MyServer(int port) : Server(port) {
    network = Network::getInstance();
}

MyServer::~MyServer() {
    delete network;
}
