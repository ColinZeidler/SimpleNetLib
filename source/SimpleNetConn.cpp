//
// Created by Colin on 2016-03-27.
//

#include <afxres.h>
#include <iostream>
#include "SimpleNetConn.h"

/**
 * attempts to establish a connection and create a new socket
 */
SimpleNetConn::SimpleNetConn(const char *serverIp, u_short port) {
    cleanup = true;
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);
    socket = ::socket(AF_INET, SOCK_STREAM, 0);

    if (socket == INVALID_SOCKET) {
        cout << "invalid socket" << endl;
        connected = false;
        return;
    }

    i_socket.sin_family = AF_INET;
    i_socket.sin_addr.S_un.S_addr = inet_addr(serverIp);
    i_socket.sin_port = htons(port);
    int ss = ::connect(socket, (struct sockaddr *)&i_socket, sizeof(i_socket));
    if (ss != 0) {
        cout << "unable to connect" << endl;
        connected = false;
        return;
    }
    connected = true;
}

SimpleNetConn::SimpleNetConn(SOCKET socket, SOCKADDR_IN i_sock) {
    this->socket = socket;
    i_socket = i_sock;
    connected = true;
    cleanup = false;
}

/**
 * ensures the connection is closed properly
 */
SimpleNetConn::~SimpleNetConn() {
    closesocket(socket);
    if (cleanup) {
        WSACleanup();
    }
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
        // TODO remove s bytes from front of buf, for now this works since everything gets sent at once
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
    char sbuff[4];
    int rLen = ::recv(socket, sbuff, 4, 0);
    if (rLen > 0) {
        uint32_t rSize = 0;
        uint32_t dSize = 0;
        dSize |= sbuff[0];
        dSize |= (sbuff[1] << 8);
        dSize |= (sbuff[2] << 16);
        dSize |= (sbuff[3] << 24);
        uint32_t remain = dSize;
        cout << "size = " << dSize << endl;
        char buff[dSize];
        while (rSize < dSize) {
            int r = ::recv(socket, buff, remain, 0);
            cout << "r = " << r << endl;
            (*data)->append(buff);
            rSize += r;
            remain -= r;
        }
        return rSize;
    } else {
        return 0;
    }
}
