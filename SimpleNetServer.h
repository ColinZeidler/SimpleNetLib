//
// Created by Colin on 2016-03-27.
//

#ifndef SIMPLENETWORKING_SIMPLENETSERVER_H
#define SIMPLENETWORKING_SIMPLENETSERVER_H
#include "SimpleNetConn.h"
#include "SimpleNetClient.h"
#include <bits/shared_ptr.h>
#include <bits/unique_ptr.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")
#define ACCEPT_TIMEOUT_S 0
#define ACCEPT_TIMEOUT_MS 250

using namespace std;
class SimpleNetServer {
public:
    SimpleNetServer(u_short port);
    ~SimpleNetServer();
    
    int acceptConnection(unique_ptr<SimpleNetClient> newConnection);
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
