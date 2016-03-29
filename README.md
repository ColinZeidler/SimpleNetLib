# SimpleNetLib
C++ library to simplify networking on windows and linux

SimpleNetServer:
 * creates and binds a socket on the specified port, starts listening
 * handles accepting incoming connections and creating SimpleNetConns from them to populate SimpleNetClients
 * closes server socket when destroyed

SimpleNetClient:
 * connects to a server on a given address and port
 * manages the contained SimpleNetConn.

SimpleNetConn:
 * handles reading and writing data, closes the connection when destroyed
 
 project is currently being built with non blocking actions in mind, so no thread management will be required. 
 Future changes will allow a choice between blocking and non blocking actions incase a multi-threaded project is desired
