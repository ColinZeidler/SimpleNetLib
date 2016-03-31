//
// Created by Colin on 2016-03-27.
//

#include <afxres.h>
#include "SimpleNetConn.h"

/**
 * attempts to establish a connection and create a new socket
 */
SimpleNetConn::SimpleNetConn(string *serverIp, u_short port) {
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);
    socket = ::socket(AF_INET, SOCK_STREAM, 0);

    if (socket == INVALID_SOCKET) {
        connected = false;
        return;
    }

    i_socket.sin_family = AF_INET;
    i_socket.sin_addr.S_un.S_addr = inet_addr(serverIp->c_str());
    i_socket.sin_port = htons(port);
    int ss = ::connect(socket, (struct sockaddr *)&i_socket, sizeof(i_socket));
    if (ss != 0) {
        connected = false;
        return;
    }
    connected = true;
}

SimpleNetConn::SimpleNetConn(SOCKET socket) {
    this->socket = socket;
    connected = true;
}

/**
 * ensures the connection is closed properly
 */
SimpleNetConn::~SimpleNetConn() {
    // TODO close connection
    closesocket(socket);
    WSACleanup();
}

/**
 * returns the number of bytes? bits? that were sent
 * data, unique_ptr<string> of data to send
 */
int SimpleNetConn::send(string **data) {
    //send size of data
    //send data
    const char *buf = (*data)->c_str();
    int bufLen = (*data)->length();
    return ::send(socket, buf, bufLen, 0);
}

/**
 * returns number of  bytes? bits? that were read
 * data, unique_ptr<string> to put the received data into
 */
int SimpleNetConn::recv(string **data) {
    char *buff;
//    int rCount = ::recv(socket, buff, )
    return 0; // TODO receive data and insert into string
}

SOCKET SimpleNetConn::getSocket() {
    return socket;
}

void SimpleNetConn::setISock(SOCKADDR_IN i_sock) {
    i_socket = i_sock;
}
