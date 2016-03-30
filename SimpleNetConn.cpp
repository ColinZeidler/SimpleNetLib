//
// Created by Colin on 2016-03-27.
//

#include "SimpleNetConn.h"

/**
 * attempts to establish a connection and create a new socket
 */
SimpleNetConn::SimpleNetConn(unique_ptr<string> serverIp) {
    connected = false;
}

SimpleNetConn::SimpleNetConn(SOCKET socket) {
    this->socket = socket;
    connected = true;
}

/**
 * ensures the connection is closed properly
 */
SimpleNetConn::~SimpleNetConn() {

}

/**
 * returns the number of bytes? bits? that were sent
 * data, unique_ptr<string> of data to send
 */
int SimpleNetConn::send(string **data) {
    return 0;
}

/**
 * returns number of  bytes? bits? that were read
 * data, unique_ptr<string> to put the received data into
 */
int SimpleNetConn::recv(string **data) {
    return 0;
}

SOCKET SimpleNetConn::getSocket() {
    return socket;
}

void SimpleNetConn::setISock(SOCKADDR_IN i_sock) {
    i_socket = i_sock;
}
