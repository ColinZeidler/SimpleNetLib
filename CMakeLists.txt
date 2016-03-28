cmake_minimum_required(VERSION 3.3)
project(SimpleNetworking)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES SimpleNetConn.cpp SimpleNetConn.h SimpleNetServer.cpp SimpleNetServer.h commons.h)
set(CLIENT_SOURCE clientMain.cpp ${SOURCE_FILES})
set(SERVER_SOURCE serverMain.cpp ${SOURCE_FILES})

add_executable(SimpleNetServer ${SERVER_SOURCE})
add_executable(SimpleNetClient ${CLIENT_SOURCE})
add_library(SimpleNetworking ${SOURCE_FILES})