cmake_minimum_required(VERSION 3.23)
project(ProxyCache)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProxyCache main.cpp src/NB_Socket.h)

if(WIN32)
    target_link_libraries(ProxyCache ws2_32)
endif()
