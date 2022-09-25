#include <iostream>
#include <thread>

#include "src/NB_Socket.h"

using namespace std;
using namespace NB;

int main() {
  Socket ProxyServer(AF_INET, SOCK_STREAM);
  ProxyServer.setSockOpt(SOL_SOCKET, SO_REUSEADDR);
  ProxyServer.Bind("127.0.0.1", 9999);
  ProxyServer.Listen(thread::hardware_concurrency());

  Socket Client;
  while((Client = ProxyServer.Accept()).getSock() != INVALID_SOCKET) {
    thread t([](const Socket& Client) {
      string request = Client.Recv(1024);
      cout << request << endl;
      Client.Send("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
      Client.Close();
    }, Client);
    t.detach();
  }


  return 0;
}
