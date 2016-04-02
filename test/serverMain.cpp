//
// Created by Colin on 2016-03-27.
//

#include <iostream>
#include "../source/SimpleNetServer.h"

using namespace std;

int main() {
    cout << "Hello, World! Server" << endl;
    SimpleNetServer server(5432);
    if (server.success != 1) {
        //failed to create server, exit
        return 0;
    }
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(true){ // main server loop
        int connResult = 0;
        SimpleNetClient *newClient = new SimpleNetClient();
        connResult = server.acceptConnection(newClient);
        if (connResult == 0) {
            cout << "new client has connected" << endl;
            // This is where a thread would be spawned for the new client
        }
        delete newClient;
    }
#pragma clang diagnostic pop
}