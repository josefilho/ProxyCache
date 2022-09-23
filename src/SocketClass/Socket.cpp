//
// Created by null on 23/09/22.
//

#include "Socket.h"

Socket::Socket(sa_family_t family, int type) : family(family), type(type), addr({}) {
    fd = socket(family, type, 0);
    if (fd == -1) {
        throw std::runtime_error("Socket create failed");
    }
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family = family;

    port = 0;
    ip = "";
}

Socket::Socket(int fd, struct sockaddr_in addr) {

}

Socket::~Socket() = default;

void Socket::setSockOpt(int level, int optname) {

}

void Socket::setAddr(sa_family_t family, uint16_t port, std::string ip) {

}

sockaddr_in Socket::getAddr() const {
    return sockaddr_in();
}

void Socket::Bind(const std::string &ip, uint16_t port) {

}

void Socket::Listen(int backlog) {

}

Socket Socket::Accept() {
    return Socket(0, 0);
}

void Socket::Connect(const std::string &ip, uint16_t port) {

}

void Socket::Close() {

}

std::string Socket::getHostByName(const std::string &hostname) {
    return std::string();
}
