//
// Created by Colin on 2016-03-27.
//

#include "SimpleNetConn.h"

/**
 * attempts to establish a connection
 */
SimpleNetConn::SimpleNetConn(unique_ptr<string> serverIp) {
    connected = false;
}

SimpleNetConn::SimpleNetConn() {
    connected = false;
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
int SimpleNetConn::send(unique_ptr<string> data) {
    return 0;
}

/**
 * returns number of  bytes? bits? that were read
 * data, unique_ptr<string> to put the received data into
 */
int SimpleNetConn::recv(unique_ptr<string> data) {
    return 0;
}

void SimpleNetConn::setSocket(SOCKET socket1) {
    socket = socket1;
}
