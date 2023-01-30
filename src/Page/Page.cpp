#include "Page.h"

Page::Page(const std::string &DATA) {
    if(DATA.empty()){
        return;
    }
    // Splitting the data into headers and body
    std::string line;
    std::stringstream ss(DATA);

    // Getting the headers
    std::vector<std::string> data;
    boost::split(data, DATA, boost::is_any_of("\r\n\r\n"));

    std::vector<std::string> _headers;
    boost::split(_headers, data[0], boost::is_any_of("\r\n"));
    for(auto &header : _headers){
        headers.push_back(header);
    }

    body = data[1];

    // Getting the host
    for(auto &header : headers){
        if(header.find("Host: ") != std::string::npos){
            host = header.substr(6);
        }
    }

    // Getting the method, path and protocol
    std::vector<std::string> _method_path_protocol;
    boost::split(_method_path_protocol, headers[0], boost::is_any_of(" "));
    method = _method_path_protocol[0];
    path = _method_path_protocol[1];
    protocol = _method_path_protocol[2];


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
