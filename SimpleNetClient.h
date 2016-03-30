//
// Created by Colin on 2016-03-28.
//

#ifndef SIMPLENETWORKING_SIMPLENETCLIENT_H
#define SIMPLENETWORKING_SIMPLENETCLIENT_H

#include <string>
#include <windows.h>
#include <bits/unique_ptr.h>
#include "SimpleNetConn.h"

using namespace std;
class SimpleNetClient {
public:
    SimpleNetClient(unique_ptr<string> address, int port);
    ~SimpleNetClient();

    void setConnection(SimpleNetConn *newConn);

    int read(string**);
    int send(string**);
private:
    SimpleNetConn *connection;
    bool connected;
};


#endif //SIMPLENETWORKING_SIMPLENETCLIENT_H
