//
// Created by horeb on 25-4-17.
//

#ifndef MOCKUPDATEPROVIDER_H
#define MOCKUPDATEPROVIDER_H

#include "provider/IUpdateProvider.h"
#include "log/Logger.h"

namespace udc {

class MockUpdateProvider final : public IUpdateProvider {
  public:
    MockUpdateProvider() = default;

    explicit MockUpdateProvider(const std::string&) {}

    ~MockUpdateProvider() override = default;

    std::string fetch() override {
        LOG_D("MockUpdateProvider::fetch");
        return std::string{};
    }

    Updates parse(const std::string& xml) override {
        LOG_D("MockUpdateProvider::parse");
        return Updates{};
    }
};

} // namespace udc

#endif // MOCKUPDATEPROVIDER_H
