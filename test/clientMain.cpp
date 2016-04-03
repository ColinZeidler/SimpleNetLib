#include <iostream>
#include "../source/SimpleNetClient.h"

using namespace std;

int main() {
    cout << "Hello, World! Client" << endl;
    SimpleNetClient client("localhost", 5432);
    if (client.isConnected()) {
        string *message = new string("Hello");
        cout << "sending: " << *message << endl;
        int size = client.send(&message);
        cout << "sent: " << size << " bytes" << endl;
        delete message;
        message = NULL;
        size = client.read(&message);
        cout << "received: " << size << " bytes" << endl;
        cout << "message received: " << *message << endl;
        delete message;
    }
    return 0;
}