//
// Created by Colin on 2016-03-27.
//

#ifndef SIMPLENETWORKING_SIMPLENETCONN_H
#define SIMPLENETWORKING_SIMPLENETCONN_H

#include <string>
#include <windows.h>

#define ACCEPT_TIMEOUT_S 0
#define ACCEPT_TIMEOUT_MS 250

using namespace std;
class SimpleNetConn {
public:
    SimpleNetConn(const char *serverIp, u_short port);
    SimpleNetConn(SOCKET socket);
    ~SimpleNetConn();

    int send(string **data);
    int recv(string **data);
    void setISock(SOCKADDR_IN i_sock);
    SOCKET getSocket();
    bool isConnected() { return connected; }
private:
    SOCKET socket;
    SOCKADDR_IN i_socket;
    bool connected;
};


#endif //SIMPLENETWORKING_SIMPLENETCONN_H
