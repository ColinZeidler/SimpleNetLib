//
// Created by Colin on 2016-03-27.
//

#include <iostream>
#include "SimpleNetServer.h"

SimpleNetServer::SimpleNetServer(u_short port) {
    success = 0;
    int err = 0;
    //Start initializing the server connection
    WSAStartup(MAKEWORD(2, 2), &Data);
    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    //set info about server socket
    i_server.sin_family = AF_INET;
    i_server.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    i_server.sin_port = htons(port);
    i_server.sin_family = AF_INET;

    //attempt to bind port
    err = bind(serverSock, (LPSOCKADDR)&i_server, sizeof(i_server));
    if (err != 0) {
        //unsuccessful in binding port
        return;
    }

    //start listening to socket
    err = listen(serverSock, 2);
    if (err == SOCKET_ERROR) {
        // there was an error attempting to listen...
        return;
    }
//    //set socket to be non blocking
//    u_long nbio = 1;
//    ioctlsocket(serverSock, FIONBIO, &nbio);
    success = 1;
}

SimpleNetServer::~SimpleNetServer() {
    closesocket(serverSock);
    WSACleanup();
}

/**
 * return codes:
 *  -1 - OK, no new client
 *  0 - OK, client accepted
 *  2 - ERROR, INVALID_SOCKET on accept
 */
int SimpleNetServer::acceptConnection(SimpleNetClient *newConnection) {
    //setup timeout
    FD_ZERO(&fd);
    FD_SET(serverSock, &fd);
    time.tv_sec = ACCEPT_TIMEOUT_S;
    time.tv_usec = ACCEPT_TIMEOUT_MS;

    if (select(0, &fd, NULL, NULL, &time) > 0) {
        SOCKADDR_IN i_client;
        int solen = sizeof(i_client);
        SimpleNetConn *newConn = new SimpleNetConn(
                accept(serverSock, (sockaddr *) &i_client, &solen));
        newConn->setISock(i_client);
        if (newConn->getSocket() == INVALID_SOCKET) {
            return 2;
        }
        newConnection->setConnection(newConn);
        return 0;
    } else {
        cout << "no new connections pending" << endl;
        return -1;
    }
}
