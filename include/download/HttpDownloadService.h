//
// Created by horeb on 25-4-18.
//

#ifndef HTTPDOWNLOADSERVICE_H
#define HTTPDOWNLOADSERVICE_H

#include "IDownloadService.h"

namespace udc {

class HttpDownloadService final : public IDownloadService {
  public:
    explicit HttpDownloadService(const std::string& repoUrl) {

    }

    ~HttpDownloadService() override;

    LocalArchiveInfo download(PackageUpdate package,
                              const std::string& destDir) override;
};

} // namespace udc

#endif // HTTPDOWNLOADSERVICE_H
