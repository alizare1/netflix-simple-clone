#include "myReq.h"

MyRequest::MyRequest() {
    network = Network::getInstance();
}

bool MyRequest::isNumber(std::string str) {
    for (int i = 0; i < str.size() ; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}