#include "Page.h"

Page::Page(const std::string &DATA) {
    if (DATA.empty()) {
        return;
    }

    data = DATA;

    // Splitting the data into headers and body
    std::vector<std::string> split_data = split(DATA, "\r\n\r\n");
    if (split_data.size() == 2) {
        headers = split(split_data[0], "\r\n");
        body = split_data[1];
    } else {
        headers = split(split_data[0], "\r\n");
    }

    // Getting the host, method, path and protocol
    std::vector<std::string> first_line = split(headers[0], " ");
    if (first_line.size() == 3) {
        method = first_line[0];
        path = first_line[1];
        protocol = first_line[2];
    }
}

std::string Page::getBody() const {
    return body;
}

std::vector<std::string> Page::getHeaders() const {
    return headers;
}

std::string Page::getHost() const {
    return host;
}

std::string Page::getMethod() const {
    return method;
}

std::string Page::getPath() const {
    return path;
}

std::string Page::getProtocol() const {
    return protocol;
}

size_t Page::getSize() const {
    return body.size() + headers.size();
}

std::string Page::getURL() const {
    return host + path;
}

Page::operator std::string() const {
    return data;
}

void Page::setProtocol(const std::string &HTTP_PROTOCOL) {
    if (HTTP_PROTOCOL.empty()) {
        return;
    }
    std::string proto;
    if (HTTP_PROTOCOL == "HTTP/1.0") {
        proto = "HTTP/1.0";
    } else {
        if (HTTP_PROTOCOL == "HTTP/1.1") {
            proto = "HTTP/1.1";
        } else {
            if (HTTP_PROTOCOL == "HTTP/2.0") {
                proto = "HTTP/2.0";
            } else {
                if (HTTP_PROTOCOL == "HTTP/3.0") {
                    proto = "HTTP/3.0";
                } else {
                    proto = "HTTP/1.1";
                }
            }
        }
    }
    headers[0] = method + " " + path + " " + proto;
    protocol = proto;
    data.replace(data.find(protocol), protocol.size(), proto);
}

std::vector<std::string> Page::split(const std::string &str, const std::string &delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) {
            pos = str.length();
        }
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) {
            tokens.push_back(token);
        }
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}
