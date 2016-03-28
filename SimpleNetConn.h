//
// Created by Colin on 2016-03-27.
//

#ifndef SIMPLENETWORKING_SIMPLENETCONN_H
#define SIMPLENETWORKING_SIMPLENETCONN_H

#include <string>
#include <bits/unique_ptr.h>
#include <windows.h>

using namespace std;
class SimpleNetConn {
public:
    SimpleNetConn(unique_ptr<string> serverIp);
    SimpleNetConn();
    ~SimpleNetConn();

    int send(unique_ptr<string> data);
    int recv(unique_ptr<string> data);
    void setSocket(SOCKET);
private:
    SOCKET socket;
    bool connected;
};


#endif //SIMPLENETWORKING_SIMPLENETCONN_H
