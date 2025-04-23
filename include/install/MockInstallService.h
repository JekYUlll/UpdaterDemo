//
// Created by horeb on 25-4-18.
//

#ifndef MOCKINSTALLSERVICE_H
#define MOCKINSTALLSERVICE_H

#include "install/IInstallService.h"
#include "log/Logger.h"
#include "model/LocalArchiveInfo.h"

namespace udc {

class MockInstallService final : public IInstallService {
  public:
    MockInstallService() = default;

    ~MockInstallService() override = default;

    InstallResult install(const LocalArchiveInfo& archive,
                          const std::string& targetDir) override {
        LOG_D("MockInstallService::install.");
        return InstallResult::success("mock/install");
    }
};

} // namespace udc

#endif // MOCKINSTALLSERVICE_H
