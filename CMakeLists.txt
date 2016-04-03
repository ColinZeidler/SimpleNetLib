cmake_minimum_required(VERSION 3.3)
project(SimpleNetworking)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES source/SimpleNetConn.cpp source/SimpleNetConn.h source/SimpleNetServer.cpp source/SimpleNetServer.h source/SimpleNetClient.cpp source/SimpleNetClient.h)
set(CLIENT_SOURCE test/clientMain.cpp)
set(SERVER_SOURCE test/serverMain.cpp)

add_executable(SimpleNetServer ${SERVER_SOURCE})
add_executable(SimpleNetClient ${CLIENT_SOURCE})
add_library(SimpleNetworking ${SOURCE_FILES})

target_link_libraries(SimpleNetworking ws2_32)

target_link_libraries(SimpleNetClient SimpleNetworking)
target_link_libraries(SimpleNetServer SimpleNetworking)