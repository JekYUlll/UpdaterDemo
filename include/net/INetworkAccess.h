//
// Created by horeb on 25-4-18.
//

#ifndef INETWORKACCESS_H
#define INETWORKACCESS_H

#include <cstdint>
#include <string>
#include <vector>

namespace udc {

class INetworkAccess {
public:
    virtual ~INetworkAccess() = default;

    virtual std::string downloadText(const std::string& url) = 0;
    virtual std::vector<uint8_t> downloadBinary(const std::string& url) = 0;
    virtual bool downloadToFile(const std::string& url, const std::string& destPath) = 0;
};

}

#endif //INETWORKACCESS_H
