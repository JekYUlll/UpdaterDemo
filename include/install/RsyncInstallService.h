//
// Created by horeb on 25-4-18.
//

#ifndef RSYNCINSTALLSERVICE_H
#define RSYNCINSTALLSERVICE_H

#include "install/IInstallService.h"

namespace udc {

class RsyncInstallService final : public IInstallService {
  public:
    RsyncInstallService();

    ~RsyncInstallService() override;

    InstallResult install(LocalArchiveInfo archive,
                          std::string targetDir) override;
};

} // namespace udc

#endif // RSYNCINSTALLSERVICE_H
