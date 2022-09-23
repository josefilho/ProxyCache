cmake_minimum_required(VERSION 3.23)
project(ProxyCache)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProxyCache main.cpp src/SocketClass/Socket.cpp src/SocketClass/Socket.h)
