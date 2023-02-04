#ifndef _SOCKET_
#define _SOCKET_

#include <string>
#include <iostream>
#include <exception>
#include <netdb.h>

#ifdef __unix // Unix

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//////////////////////////////
/// @class Socket
/// @brief Represents a socket with steroids
/// @author Filho, Jose Carlos - 2023
/// @example Server
/// @code
/// Socket server(AF_INET, SOCK_STREAM, true);
/// server.setSockOptions(SO_REUSEADDR | SO_REUSEPORT);
/// server.Bind("127.0.0.1", 8080);
/// server.Listen(10);
/// Socket client = server.Accept();
/// client.send("Hello World!");
/// client.Close();
/// server.Close();
//////////////////////////////
class Socket {
private:
    sa_family_t family;   // Socket family
    int type;             // Socket type
    int fd;               // Socket file descriptor
    sockaddr_in addr{};   // Socket address
    int protocol;         // Socket protocol
    uint16_t port{};      // Socket port
    std::string ip;       // Socket ip
    bool server;          // Is socket server

public:
    //////////////////////////////
    /// @brief Socket constructor
    /// @param FAMILY Socket family
    /// @param TYPE Socket type
    /// @param SERVER Is socket server (default: false)
    /// @param PROTOCOL Socket protocol (default: 0)
    /// @throw std::runtime_error if socket creation failed
    //////////////////////////////
    explicit Socket(sa_family_t FAMILY, int TYPE, bool SERVER = false, int PROTOCOL = 0);

    //////////////////////////////
    /// @brief Socket constructor
    /// @param FD Socket file descriptor
    /// @param ADDR Socket address
    /// @param TYPE Socket type (default: SOCK_STREAM)
    /// @param PROTOCOL Socket protocol (default: 0)
    //////////////////////////////
    explicit Socket(int FD, sockaddr_in ADDR, int TYPE = SOCK_STREAM, int PROTOCOL = 0);

    //////////////////////////////
    /// @brief Socket constructor
    /// @param FAMILY Socket family
    /// @param IP Socket ip
    /// @param PORT Socket port
    /// @param TYPE Socket type (default: SOCK_STREAM)
    /// @param PROTOCOL Socket protocol (default: 0)
    /// @throw std::runtime_error if socket creation failed
    /// @throw std::runtime_error if invalid address
    //////////////////////////////
    explicit Socket(sa_family_t FAMILY, const std::string &IP, uint16_t PORT, int TYPE = SOCK_STREAM, int PROTOCOL = 0);

    //////////////////////////////
    /// @brief Socket destructor
    //////////////////////////////
    ~Socket();

    //////////////////////////////
    /// @brief Set socket options
    /// @param OPTNAME Socket option name (default: SO_REUSEADDR | SO_REUSEPORT)
    /// @return true if success, false otherwise
    //////////////////////////////
    [[nodiscard]] bool setSockOptions(int OPTNAME = SO_REUSEADDR | SO_REUSEPORT) const;

    //////////////////////////////
    /// @brief Accept connection
    /// @return Socket object
    /// @throw std::runtime_error if accept failed
    //////////////////////////////
    [[nodiscard]] Socket Accept() const;

    //////////////////////////////
    /// @brief Receive data
    /// @param SIZE Data size
    /// @return Data
    /// @throw std::runtime_error if recv failed
    //////////////////////////////
    [[nodiscard]] std::string Receive(int SIZE) const;

    //////////////////////////////
    /// @brief Bind socket
    /// @param IP Socket ip
    /// @param PORT Socket port
    /// @throw std::runtime_error if bind failed
    //////////////////////////////
    void Bind(const std::string &IP, int PORT);

    //////////////////////////////
    /// @brief Listen for connections
    /// @param BACKLOG Backlog (default: 10)
    /// @throw std::runtime_error if listen failed
    //////////////////////////////
    void Listen(int BACKLOG = 10) const;

    //////////////////////////////
    /// @brief Send data
    /// @param MSG Data
    /// @throw std::runtime_error if send failed
    //////////////////////////////
    void Send(const std::string &MSG) const;

    //////////////////////////////
    /// @brief Connect to server
    /// @param IP Server ip
    /// @param PORT Server port
    /// @throw std::runtime_error if invalid address
    /// @throw std::runtime_error if connect failed
    /// @throw std::logic_error if socket is a server
    //////////////////////////////
    void Connect(const std::string &IP, int PORT);

    //////////////////////////////
    /// @brief set socket address
    /// @param FAMILY Socket family
    /// @param IP Socket ip
    /// @param PORT Socket port
    /// @throw std::runtime_error if invalid address
    //////////////////////////////
    void setAddr(sa_family_t FAMILY, const std::string &IP, int PORT);

    //////////////////////////////
    /// @brief Get socket address
    /// @return Socket address
    //////////////////////////////
    [[nodiscard]] sockaddr_in getAddr() const;

    //////////////////////////////
    /// @brief Close socket connection
    /// @throw std::runtime_error if close failed
    //////////////////////////////
    void Close() const;

    //////////////////////////////
    /// @brief Get ip address from host name
    /// @param HOST Host name
    /// @return Ip address
    //////////////////////////////
    static std::string getHostByName(const std::string &HOST);
};

#endif // __unix

#ifdef _WIN32 // Windows
#include <winsock2.h>
#include <ws2tcpip.h>
#endif // _WIN32


#endif  // _SOCKET_