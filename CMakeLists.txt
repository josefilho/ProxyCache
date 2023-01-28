cmake_minimum_required(VERSION 3.23)
project(ProxyCache)

set(CMAKE_CXX_STANDARD 20)

add_executable(Server Server.cpp src/Socket/Socket.h src/Socket/Socket.cpp)
add_executable(Client Client.cpp src/Socket/Socket.h src/Socket/Socket.cpp)

if(WIN32)
    target_link_libraries(Server ws2_32)
    target_link_libraries(Client ws2_32)
endif()
