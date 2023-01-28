#include "Socket.h"

#ifdef __unix

Socket::Socket(sa_family_t FAMILY, int TYPE, bool SERVER, int PROTOCOL):
               family(FAMILY), type(TYPE), server(SERVER), protocol(PROTOCOL) {
    fd = socket(family, type, protocol);
    if (fd == -1) {
        throw std::runtime_error("Socket: Socket creation failed");
    }

    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = family;
}

Socket::Socket(int FD, sockaddr_in ADDR, int TYPE, int PROTOCOL):
               fd(FD), addr(ADDR), family(ADDR.sin_family), server(false), type(TYPE), protocol(PROTOCOL) {
    port = ntohs(addr.sin_port);
    ip = inet_ntoa(addr.sin_addr);
}

Socket::~Socket() {
    close(fd);
}

bool Socket::setSockOptions(int OPTNAME) const {
    int optval = 1;
    if (setsockopt(fd, SOL_SOCKET, OPTNAME, &optval, sizeof(optval)) == -1) {
        return false;
    }
    return true;
}

void Socket::Bind(const std::string& IP, int PORT) {
    port = PORT;
    ip = IP;
    addr.sin_port = htons(port);
    if (inet_pton(family, ip.c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("Socket(Bind): Invalid address");
    }
    if (bind(fd, (sockaddr*)&addr, sizeof(addr)) == -1) {
        throw std::runtime_error("Socket(Bind): Bind failed");
    }
}

void Socket::Listen(int BACKLOG) const {
    if(!server)
        throw std::logic_error("Socket(Listen): Not a server");
    if(BACKLOG < 0)
        throw std::invalid_argument("Socket(Listen): Invalid backlog");
    if (listen(fd, BACKLOG) == -1) {
        throw std::runtime_error("Socket(Listen): Listen failed");
    }
}

Socket Socket::Accept() const {
    int new_fd;
    sockaddr_in new_addr{};
    socklen_t addrlen = sizeof(new_addr);
    if ((new_fd = accept(fd, (sockaddr*)&new_addr, &addrlen)) == -1) {
        throw std::runtime_error("Socket(Accept): Accept failed");
    }
    return Socket(new_fd, new_addr);
}

std::string Socket::Recv(int SIZE) const {
    char buffer[SIZE];
    ssize_t valread = read(fd, buffer, SIZE);
    if (valread == -1) {
        throw std::runtime_error("Socket(Recv): Recv failed");
    }
    return {buffer, (unsigned long)valread };
}

void Socket::Send(const std::string &MSG) const {
    if (send(fd, MSG.c_str(), MSG.length(), 0) == -1) {
        throw std::runtime_error("Socket(Send): Send failed");
    }
}

void Socket::Connect(const std::string &IP, int PORT) {
    port = PORT;
    ip = IP;
    addr.sin_port = htons(port);
    if (inet_pton(family, ip.c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("Socket(Connect): Invalid address");
    }
    if (connect(fd, (sockaddr*)&addr, sizeof(addr)) == -1) {
        throw std::runtime_error("Socket(Connect): Connect failed");
    }
}

void Socket::setAddr(sa_family_t FAMILY, const std::string& IP, int PORT) {
    family = FAMILY;
    port = PORT;
    ip = IP;
    addr.sin_family = family;
    addr.sin_port = htons(port);
    if (inet_pton(family, ip.c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("Socket(setAddr): Invalid address");
    }

}

sockaddr_in Socket::getAddr() const {
    return addr;
}

#endif // __unix
