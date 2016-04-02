//
// Created by Colin on 2016-03-27.
//

#ifndef SIMPLENETWORKING_SIMPLENETSERVER_H
#define SIMPLENETWORKING_SIMPLENETSERVER_H
#include "SimpleNetConn.h"
#include "SimpleNetClient.h"
#include <windows.h>


using namespace std;
class SimpleNetServer {
public:
    SimpleNetServer(u_short port);
    ~SimpleNetServer();
    
    int acceptConnection(SimpleNetClient *newConnection);
private:

//variables
public:
    int success;
    
private:
    SOCKET serverSock;
    SOCKADDR_IN i_server;
    WSADATA Data;

    fd_set fd;
    timeval time;
};


#endif //SIMPLENETWORKING_SIMPLENETSERVER_H