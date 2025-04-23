//
// Created by horeb on 25-4-18.
//

#ifndef MOCKDOWNLOADSERVICE_H
#define MOCKDOWNLOADSERVICE_H

#include "download/IDownloadService.h"
#include "log/Logger.h"
#include "model/LocalArchiveInfo.h"

namespace udc {

class MockDownloadService final : public IDownloadService {
  public:
    MockDownloadService() = default;
    ~MockDownloadService() override = default;
    LocalArchiveInfo download(PackageUpdate package,
                              const std::string& destDir) override {
        LOG_D("MockDownloadService::download to {}.", destDir);
        return LocalArchiveInfo{
            "mock/local/dir",
        };
    }
};
} // namespace udc

#endif // MOCKDOWNLOADSERVICE_H
