//
// Created by Colin on 2016-03-28.
//

#include "SimpleNetClient.h"

SimpleNetClient::SimpleNetClient(string *address, u_short port) {
    connected = false;
    connection = new SimpleNetConn(address->c_str(), port);
    if (connection->isConnected()) {
        connected = true;
    }
}

SimpleNetClient::SimpleNetClient(const char *address, u_short port) {
    connected = false;
    connection = new SimpleNetConn(address, port);
    if (connection->isConnected()) {
        connected = true;
    }
}

SimpleNetClient::SimpleNetClient() {
}

SimpleNetClient::~SimpleNetClient() {
    delete connection;
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




