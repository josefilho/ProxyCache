//
// Created by null on 23/09/22.
//

#ifndef PROXYCACHE_SOCKET_H
#define PROXYCACHE_SOCKET_H

#ifdef __unix__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)

#include <winsock2.h>

#endif

#include <string>
#include <stdexcept>

class Socket {
private:
    sa_family_t family;
    int type;
    int fd;
    struct sockaddr_in addr;
    uint16_t port;
    std::string ip;

public:
    Socket(sa_family_t family, int type);
    Socket(int fd, struct sockaddr_in addr);
    ~Socket();

    void setSockOpt(int level, int optname);
    void setAddr(sa_family_t family, uint16_t port, std::string ip);

    sockaddr_in getAddr() const;

    void Bind(const std::string &ip, uint16_t port);
    void Listen(int backlog);
    Socket Accept();
    void Connect(const std::string &ip, uint16_t port);
    void Close();

    static std::string getHostByName(const std::string &hostname);
};


#endif //PROXYCACHE_SOCKET_H
