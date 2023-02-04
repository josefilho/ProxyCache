//
// Created by nullbyte on 1/29/23.
//

#ifndef PROXYCACHE_PAGE_H
#define PROXYCACHE_PAGE_H

#include <string>
#include <vector>

class Page {
private:
    std::string data;
    std::vector<std::string> headers;
    std::string body;
    std::string host;
    std::string method;
    std::string path;
    std::string protocol;

    static std::vector<std::string> split(const std::string& str, const std::string& delim);

public:
    explicit Page(const std::string& DATA);

    [[nodiscard]] std::string getBody() const;
    [[nodiscard]] std::vector<std::string> getHeaders() const;
    [[nodiscard]] std::string getHost() const;
    [[nodiscard]] std::string getMethod() const;
    [[nodiscard]] std::string getPath() const;
    [[nodiscard]] std::string getProtocol() const;
    [[nodiscard]] size_t getSize() const;
    [[nodiscard]] std::string getURL() const;

    void setProtocol(const std::string& HTTP_PROTOCOL);

    explicit operator std::string() const;
};


#endif //PROXYCACHE_PAGE_H
