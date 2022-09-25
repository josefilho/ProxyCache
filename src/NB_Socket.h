//
// Created by NullByte on 24/09/2022.
//

#ifndef _NB_SOCKET_H
#define _NB_SOCKET_H

#include <stdexcept>
#include <winsock2.h>

namespace NB {
  class Socket {
    private:
      WSAData wsaData;
      SOCKET sock;
      struct sockaddr_in addr;
      uint16_t port;
      std::string ip;
      uint8_t family;
      uint8_t type;
      uint8_t protocol;

      void Init();

    public:
      //--------------------------------------------- CONSTRUCTORS -----------------------------------------------------
      Socket(uint8_t family, uint8_t type, uint8_t protocol = IPPROTO_TCP);

      Socket(SOCKET fd, struct sockaddr_in addr);

      Socket();

      ~Socket() = default;

      //------------------------------------------------ FUNCTIONS -----------------------------------------------------
      void Close() const;

      void setSockOpt(int level, int optname) const;

      void Bind(const std::string &ip, uint16_t port);

      void Listen(unsigned int backlog) const;

      void Connect(const std::string &ip, uint16_t port);

      [[nodiscard]] Socket Accept() const;

      void Send(const std::string &msg) const;

      [[nodiscard]] std::string Recv(int len) const;

      //----------------------------------------- GETTERS AND SETTERS --------------------------------------------------
      [[nodiscard]] SOCKET getSock() const;

      [[nodiscard]] uint16_t getPort() const;

      [[nodiscard]] std::string getIP() const;

      [[nodiscard]] uint8_t getFamily() const;

      [[nodiscard]] uint8_t getType() const;

      [[nodiscard]] uint8_t getProtocol() const;

      //----------------------------------------------- OPERATORS ------------------------------------------------------

      Socket& operator=(const Socket& other);
  };
}

void NB::Socket::Init() {
  int iResult = WSAStartup(MAKEWORD(2, 2), &(this->wsaData));
  if (iResult != 0) {
    throw std::runtime_error(&"WSAStartup failed: "[iResult]);
  }
}

NB::Socket::Socket(uint8_t family, uint8_t type, uint8_t protocol) : wsaData({}), addr({}), family(family), type(type),
                                                                     protocol(protocol) {
  Socket::Init();
  this->sock = socket(family, type, protocol);
  if (this->sock == INVALID_SOCKET) {
    throw std::runtime_error(&"Error at socket(): "[WSAGetLastError()]);
  }
  addr.sin_family = family;
  addr.sin_addr.s_addr = INADDR_ANY;

  this->port = 0;
  this->ip = "";
}

NB::Socket::Socket(SOCKET fd, struct sockaddr_in addr) : wsaData({}), addr(addr), sock(fd), family(AF_INET),
                                                         type(SOCK_STREAM),
                                                         protocol(IPPROTO_TCP) {
  Socket::Init();
  this->port = ntohs(addr.sin_port);
  this->ip = inet_ntoa(addr.sin_addr);
}

void NB::Socket::Close() const {
  closesocket(this->sock);
  WSACleanup();
}

NB::Socket::Socket() : wsaData({}), addr({}), sock(INVALID_SOCKET), family(AF_INET), type(SOCK_STREAM),
                       protocol(IPPROTO_TCP) {
  Socket::Init();

  this->port = 0;
  this->ip = "";

}

void NB::Socket::setSockOpt(int level, int optname) const {
  int optval = 1;
  int optlen = sizeof(optval);
  if (setsockopt(this->sock, level, optname, (char *) &optval, optlen) == SOCKET_ERROR) {
    throw std::runtime_error(&"setsockopt() failed: "[WSAGetLastError()]);
  }
}

void NB::Socket::Bind(const std::string &_ip, uint16_t _port) {
  this->ip = _ip;
  this->port = _port;
  addr.sin_port = htons(_port);
  addr.sin_addr.s_addr = inet_addr(_ip.c_str());
  if (bind(this->sock, (SOCKADDR *) &addr, sizeof(addr)) == SOCKET_ERROR) {
    throw std::runtime_error(&"bind() failed: "[WSAGetLastError()]);
  }
}

void NB::Socket::Listen(unsigned int backlog) const {
  if (listen(this->sock, (int)backlog) == SOCKET_ERROR) {
    throw std::runtime_error(&"listen() failed: "[WSAGetLastError()]);
  }
}

void NB::Socket::Connect(const std::string &_ip, uint16_t _port) {
  this->ip = _ip;
  this->port = _port;
  addr.sin_port = htons(_port);
  addr.sin_addr.s_addr = inet_addr(_ip.c_str());
  if (connect(this->sock, (SOCKADDR *) &addr, sizeof(addr)) == SOCKET_ERROR) {
    throw std::runtime_error(&"connect() failed: "[WSAGetLastError()]);
  }
}

NB::Socket NB::Socket::Accept() const {
  struct sockaddr_in client_addr{};
  int client_addr_size = sizeof(client_addr);
  SOCKET client_sock = accept(this->sock, (SOCKADDR *) &client_addr, &client_addr_size);
  if (client_sock == INVALID_SOCKET) {
    throw std::runtime_error(&"accept() failed: "[WSAGetLastError()]);
  }
  return {client_sock, client_addr};
}

void NB::Socket::Send(const std::string &msg) const {
  ssize_t bytes_sent = send(this->sock, msg.c_str(), (int)msg.size(), 0);
  if (bytes_sent == SOCKET_ERROR) {
    throw std::runtime_error(&"send() failed: "[WSAGetLastError()]);
  }
}

std::string NB::Socket::Recv(int len) const {
  char *buffer = new char[len + 1];
  ssize_t bytes_recv = recv(this->sock, buffer, len, 0);
  if (bytes_recv == SOCKET_ERROR) {
    throw std::runtime_error(&"recv() failed: "[WSAGetLastError()]);
  }
  buffer[bytes_recv] = '\0';
  std::string msg(buffer);
  delete[] buffer;
  return msg;
}


SOCKET NB::Socket::getSock() const {
  return this->sock;
}

uint16_t NB::Socket::getPort() const {
  return this->port;
}

std::string NB::Socket::getIP() const {
  return this->ip;
}

uint8_t NB::Socket::getFamily() const {
  return this->family;
}

uint8_t NB::Socket::getType() const {
  return this->type;
}

uint8_t NB::Socket::getProtocol() const {
  return this->protocol;
}

NB::Socket &NB::Socket::operator=(const NB::Socket &other) {
  this->sock = other.sock;
  this->addr = other.addr;
  this->port = other.port;
  this->ip = other.ip;
  this->family = other.family;
  this->type = other.type;
  this->protocol = other.protocol;
  return *this;
}



#endif //_NB_SOCKET_H
