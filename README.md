# SimpleNetLib
C++ library to simplify networking on windows and linux

## Classes
SimpleNetServer:
 * creates and binds a socket on the specified port, starts listening
 * handles accepting incoming connections and creating SimpleNetConns from them to populate SimpleNetClients
 * closes server socket when destroyed

SimpleNetClient:
 * connects to a server on a given address and port
 * manages the contained SimpleNetConn.

SimpleNetConn:
 * handles reading and writing data, closes the connection when destroyed
 
## Messaging
When sending data the transmitting client will send the size of the data in 4 bytes, followed by the data. The receiver will read in the first 4 bytes, assemble the data into a uint32_t that represent the data size and then read until it has proccessed the full size of the data.

### Sending
Sending data does not pose any blocking issues.

The uint32 size of the data will need to be converted into an array of 4 chars to fit the send cuntion that requires a char* for the data. The LSB of the size will go in the 0 position of the data array, the MSB will go in the 3 position.

EX: size = 0x80008602 = char[0x02, 0x86, 0x00, 0x80] = data

send methods, several to handle different data types, with one that handles anything if the size is specified

    send(string** string) //simple string message sending
    send(void* data, uint32_t size) //for all other structs

### Recieving
Recieving will default to a non blocking operation for the first read, after recieving the data size it will continue to run blocking reads until the full data set has been read. The non blocking behaviour can be changed if the user requires.

The size of the data from the first 4 byte read will have to be converted from a char* into a uint32. The 0 position will be the LSB, and the 3 position will be the MSB of the size.

EX: data = char[0x02, 0x86, 0x00, 0x80] = 0x80008602 = size

## Threading decisions
Project is currently being built with blocking actions in mind. The user will have to manage the threads that they require if they wish to have their prgram continue while waiting for an accept or recv.
