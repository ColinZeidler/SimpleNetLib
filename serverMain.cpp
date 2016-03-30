//
// Created by Colin on 2016-03-27.
//

#include <iostream>
#include <bits/unique_ptr.h>
#include "SimpleNetServer.h"

using namespace std;

int main() {
    cout << "Hello, World! Server" << endl;
    unique_ptr<SimpleNetServer> server(new SimpleNetServer(5432));
    if (server->success != 1) {
        //failed to create server, exit
        return 0;
    }
}