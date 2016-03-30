//
// Created by Colin on 2016-03-28.
//

#include "SimpleNetClient.h"

SimpleNetClient::SimpleNetClient(unique_ptr<string> address, int port) {
    // TODO attempt to connect to remote server at address, port
}

SimpleNetClient::~SimpleNetClient() {
    // TODO close connection
}

int SimpleNetClient::read(string **ptr) {
    return this->connection->recv(ptr);
}

int SimpleNetClient::send(string **ptr) {
    return this->connection->send(ptr);
}

void SimpleNetClient::setConnection(SimpleNetConn *newConn) {
    connection = newConn;
    connected = true;
}
