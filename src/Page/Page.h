//
// Created by nullbyte on 1/29/23.
//

#ifndef PROXYCACHE_PAGE_H
#define PROXYCACHE_PAGE_H

#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

class Page {
private:
    std::vector<std::string> headers;
    std::string body;
    std::string host;
    std::string method;
    std::string path;
    std::string protocol;

public:
    explicit Page(const std::string& DATA);

    [[nodiscard]] std::string getBody() const;
    [[nodiscard]] std::vector<std::string> getHeaders() const;
    [[nodiscard]] std::string getHost() const;
    [[nodiscard]] std::string getMethod() const;
    [[nodiscard]] std::string getPath() const;
    [[nodiscard]] std::string getProtocol() const;
};


#endif //PROXYCACHE_PAGE_H
