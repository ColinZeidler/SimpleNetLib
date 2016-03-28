//
// Created by Colin on 2016-03-27.
//

#include <winsock2.h>
#include "SimpleNetServer.h"

SimpleNetServer::SimpleNetServer(u_short port) {
    clients = 0;
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

}

/**
 * return codes:
 *  0 - OK, client accepted
 *  1 - ERROR, too many clients
 *  2 - ERROR, INVALID_SOCKET on accept
 */
int SimpleNetServer::acceptConnection(unique_ptr<SimpleNetConn> newConnection) {
    //setup timeout
    FD_ZERO(&fd);
    FD_SET(serverSock, &fd);
    time.tv_sec = ACCEPT_TIMEOUT_S;
    time.tv_usec = ACCEPT_TIMEOUT_MS;

    if (select(0, &fd, NULL, NULL, &time) > 0) {
        int solen = sizeof(i_client);
        clientSocks[clients] = accept(serverSock, (sockaddr *) &i_client, &solen);
        if (clientSocks[clients] == INVALID_SOCKET) {
            return 2;
        }
    }
}
