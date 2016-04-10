//
// Created by Colin on 2016-03-27.
//

#ifndef SIMPLENETWORKING_SIMPLENETSERVER_H
#define SIMPLENETWORKING_SIMPLENETSERVER_H
#include "SimpleNetConn.h"
#include "SimpleNetClient.h"

#ifdef USE_WINDOWS
#include <windows.h>
#endif

#ifdef USE_UNIX
#include <sys/socket.h>
#endif


using namespace std;
class SimpleNetServer {
public:
    SimpleNetServer(u_short port);
    ~SimpleNetServer();
    
    int acceptConnection(SimpleNetClient *newClient);
private:

//variables
public:
    int success;
    
private:
#ifdef USE_WINDOWS
    SOCKET serverSock;
    SOCKADDR_IN i_server;
    WSADATA Data;
#endif

};


#endif //SIMPLENETWORKING_SIMPLENETSERVER_H
