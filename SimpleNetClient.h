//
// Created by Colin on 2016-03-28.
//

#ifndef SIMPLENETWORKING_SIMPLENETCLIENT_H
#define SIMPLENETWORKING_SIMPLENETCLIENT_H

#include <string>
#include <windows.h>
#include <memory>
#include "SimpleNetConn.h"

using namespace std;
class SimpleNetClient {
public:
    SimpleNetClient(unique_ptr<string> address, int port);
    ~SimpleNetClient();

    void setConnection(shared_ptr<SimpleNetConn> newConn);

    int read(unique_ptr<string>);
    int send(unique_ptr<string>);
private:
    shared_ptr<SimpleNetConn> connection;
    bool connected;
};


#endif //SIMPLENETWORKING_SIMPLENETCLIENT_H
