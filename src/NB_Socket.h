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
      Socket(uint8_t family, uint8_t type, uint8_t protocol = IPPROTO_TCP);
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


#endif //_NB_SOCKET_H
