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
    uint32_t dSize = (uint32_t)(*data)->length();
    uint32_t sSize = 0;
    uint32_t remain = dSize;
    //send size of data
    char sizeBuf[4];
    sizeBuf[0] = (char)(dSize & 0xFF);
    sizeBuf[1] = (char)((dSize >> 8) & 0xFF);
    sizeBuf[2] = (char)((dSize >> 16) & 0xFF);
    sizeBuf[3] = (char)((dSize >> 24) & 0xFF);
    ::send(socket, sizeBuf, 4, 0);
    //send data
    const char *buf = (*data)->c_str();
    while (sSize < dSize) {
        // TODO remove s bytes from front of buf
        int s = ::send(socket, buf, remain, 0);
        sSize += s;
        remain -= s;
    }
    return sSize;
}

/**
 * returns number of  bytes? bits? that were read
 * data, unique_ptr<string> to put the received data into
 *
 * calling scope is responsible for cleaning up string pointer.
 */
int SimpleNetConn::recv(string **data) {
    (*data) = new string();
    char buff[256];
    int rLen = ::recv(socket, buff, 4, 0);
    if (rLen > 0) {
        uint32_t rSize = 0;
        uint32_t dSize = 0;
        dSize |= buff[0];
        dSize |= (buff[1] << 8);
        dSize |= (buff[2] << 16);
        dSize |= (buff[3] << 24);
        uint32_t remain = dSize;

        while (rSize < dSize) {
            int r = ::recv(socket, buff, remain, 0);
            (*data)->append(buff);
            rSize += r;
            remain -= r;
        }
        return rSize;
    } else {
        return 0;
    }
}

SOCKET SimpleNetConn::getSocket() {
    return socket;
}

void SimpleNetConn::setISock(SOCKADDR_IN i_sock) {
    i_socket = i_sock;
}