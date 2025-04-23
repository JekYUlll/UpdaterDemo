//
// Created by horeb on 25-4-18.
//

#ifndef ZIPINSTALLSERVICE_H
#define ZIPINSTALLSERVICE_H

#include "install/IInstallService.h"
#include "model/LocalArchiveInfo.h"

namespace udc {

class ZipInstallService final : public IInstallService {
  public:
    ~ZipInstallService() override = default;

    InstallResult install(const LocalArchiveInfo& archive,
                          const std::string& targetDir) override {

        return InstallResult::success(targetDir);
    }
};

}

#endif //ZIPINSTALLSERVICE_H
