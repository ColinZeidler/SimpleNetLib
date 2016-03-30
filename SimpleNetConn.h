//
// Created by Colin on 2016-03-27.
//

#ifndef SIMPLENETWORKING_SIMPLENETCONN_H
#define SIMPLENETWORKING_SIMPLENETCONN_H

#include <string>
#include <memory>
#include <windows.h>

using namespace std;
class SimpleNetConn {
public:
    SimpleNetConn(unique_ptr<string> serverIp);
    SimpleNetConn(SOCKET socket);
    ~SimpleNetConn();

    int send(unique_ptr<string> data);
    int recv(unique_ptr<string> data);
    void setISock(SOCKADDR_IN i_sock);
    SOCKET getSocket();
private:
    SOCKET socket;
    SOCKADDR_IN i_socket;
    bool connected;
};


#endif //SIMPLENETWORKING_SIMPLENETCONN_H
