//
// Created by Colin on 2016-03-27.
//

#ifndef SIMPLENETWORKING_SIMPLENETCONN_H
#define SIMPLENETWORKING_SIMPLENETCONN_H

#include <string>
#ifdef USE_WINDOWS
#include <windows.h>
#endif
#ifdef USE_UNIX
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
typedef int SOCKET;
#endif

#define ACCEPT_TIMEOUT_S 0
#define ACCEPT_TIMEOUT_MS 250

using namespace std;
class SimpleNetConn {
public:
    SimpleNetConn(const char *serverIp, u_short port);
    SimpleNetConn(SOCKET socket, SOCKADDR_IN i_sock);
    ~SimpleNetConn();

    int send(string **data);
    int recv(string **data);
    SOCKET getSocket() { return socket; }
    bool isConnected() { return connected; }
private:
    SOCKET socket;
    SOCKADDR_IN i_socket;
    bool connected;
    bool cleanup;
};


#endif //SIMPLENETWORKING_SIMPLENETCONN_H
