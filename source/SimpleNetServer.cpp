//
// Created by Colin on 2016-03-27.
//

#include <iostream>
#include "SimpleNetServer.h"

SimpleNetServer::SimpleNetServer(u_short port) {
#ifdef USE_WINDOWS
    cout << "WINDOWS Server" << endl;
#endif
#ifdef USE_UNIX
    cout << "UNIX Server" << endl;
#endif
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
        cout << "unable to bind port" << endl;
        return;
    }

    //start listening to socket
    err = listen(serverSock, 2);
    if (err == SOCKET_ERROR) {
        cout << "unable to listen on port" << endl;
        return;
    }
    success = 1;
}

SimpleNetServer::~SimpleNetServer() {
    closesocket(serverSock);
    WSACleanup();
}

/**
 * return codes:
 *  0 - OK, client accepted
 *  2 - ERROR, INVALID_SOCKET on accept
 */
int SimpleNetServer::acceptConnection(SimpleNetClient *newClient) {
    SOCKADDR_IN i_client;
    int solen = sizeof(i_client);
    SOCKET s = accept(serverSock, (sockaddr *) &i_client, &solen);
    SimpleNetConn *newConn = new SimpleNetConn(s, i_client);
    if (s == INVALID_SOCKET) {
        cout << "error invalid socket" << endl;
        return 2;
    }
    newClient->setConnection(newConn);
    return 0;
}
