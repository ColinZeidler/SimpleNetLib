//
// Created by Colin on 2016-03-28.
//

#ifndef SIMPLENETWORKING_SIMPLENETCLIENT_H
#define SIMPLENETWORKING_SIMPLENETCLIENT_H

#include <string>
#include <windows.h>
#include "SimpleNetConn.h"

using namespace std;
class SimpleNetClient {
public:
    SimpleNetClient(string *address, u_short port);
    SimpleNetClient(const char *address, u_short port);
    SimpleNetClient();
    ~SimpleNetClient();

    void setConnection(SimpleNetConn *newConn);
    bool isConnected() { return connected; }

    int read(string**);
    int send(string**);
private:
    SimpleNetConn *connection;
    bool connected;
};


#endif //SIMPLENETWORKING_SIMPLENETCLIENT_H
