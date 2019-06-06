#ifndef REQUEST_H
#define REQUEST_H

#include "structs.h"
#include <map>
#include <string>
#include <functional>
#include <iostream>
#include "network.h"
#include "defines.h"
#include "exceptions.h"

class Network;

class MyRequest {
public: 
    MyRequest();
protected:
    bool isNumber(std::string str);

    Network* network;
};

#endif