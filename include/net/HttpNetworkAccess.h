//
// Created by horeb on 25-4-18.
//

#ifndef HTTPNETWORKACCESS_H
#define HTTPNETWORKACCESS_H

#include "net/INetworkAccess.h"

#include <cpr/cpr.h>

namespace udc {

class HttpNetworkAccess final : public INetworkAccess {
  public:
    HttpNetworkAccess() = default;
    ~HttpNetworkAccess() override = default;

    std::string downloadText(const std::string& url) override {
        LOG_D("HttpNetworkAccess::downloadText from {}.", url);
        auto r = Get(cpr::Url{url});
        if (r.status_code != 200)
            throw std::runtime_error("Failed to fetch");
        return r.text;
    }

    std::vector<uint8_t> downloadBinary(const std::string& url) override {
        LOG_D("HttpNetworkAccess::downloadBinary from {}.", url);
        auto r = Get(cpr::Url{url});
        if (r.status_code != 200) {
            throw std::runtime_error("Failed to fetch binary: HTTP " +
                                     std::to_string(r.status_code));
        }
        std::vector<uint8_t> bytes(r.text.begin(), r.text.end());
        return bytes;
    }

    bool downloadToFile(const std::string& url,
                        const std::string& destPath) override {
        LOG_D("HttpNetworkAccess::downloadToFile from {} to {}.", url, destPath);
        std::ofstream output(destPath, std::ios::binary);
        if (!output) {
            throw std::runtime_error("Cannot open file for writing: " +
                                     destPath);
        }
        cpr::WriteCallback write_cb(
            [&output](const std::string_view& data, intptr_t) -> bool {
                output.write(data.data(), data.size());
                return true;
            });
        const auto r = Get(cpr::Url{url}, write_cb);
        output.close();
        return r.status_code == 200;
    }
};

} // namespace udc

#endif // HTTPNETWORKACCESS_H
