#ifndef _SOCKET_
#define _SOCKET_

#include <string>
#include <iostream>
#include <exception>

#ifdef __unix // Unix

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket {
private:
    sa_family_t family;
    int type;
    int fd;
    sockaddr_in addr{};
    int protocol;
    uint16_t port{};
    std::string ip;
    bool server;

public:
    explicit Socket(sa_family_t FAMILY, int TYPE, bool SERVER = false, int PROTOCOL = 0);
    explicit Socket(int FD, sockaddr_in ADDR, int TYPE = SOCK_STREAM, int PROTOCOL = 0);
    ~Socket();

    [[nodiscard]] bool setSockOptions(int OPTNAME = SO_REUSEADDR | SO_REUSEPORT) const;
    [[nodiscard]] Socket Accept() const;
    [[nodiscard]] std::string Recv(int SIZE) const;
    void Bind(const std::string& IP, int PORT);
    void Listen(int BACKLOG) const;
    void Send(const std::string& MSG) const;
    void Connect(const std::string& IP, int PORT);

    void setAddr(sa_family_t FAMILY, const std::string& IP, int PORT);
    sockaddr_in getAddr() const;
};

#endif // __unix

#ifdef _WIN32 // Windows
#include <winsock2.h>
#include <ws2tcpip.h>
#endif // _WIN32


#endif  // _SOCKET_