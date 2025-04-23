//
// Created by horeb on 25-4-19.
//

#ifndef MOCKSELECTOR_H
#define MOCKSELECTOR_H

#include "log/Logger.h"
#include "selector/IPackageSelector.h"

namespace udc {

class MockSelector final : public IPackageSelector {
  public:
    MockSelector() = default;

    ~MockSelector() override = default;

    std::vector<PackageUpdate> select(Updates& updates,
                                      const Version& currentVersion) override {
        LOG_D("MockSelector::select");
        return {};
    }
};

} // namespace udc

#endif // MOCKSELECTOR_H
