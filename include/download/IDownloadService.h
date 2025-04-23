//
// Created by horeb on 25-4-17.
//

#ifndef IDOWNLOADSERVICE_H
#define IDOWNLOADSERVICE_H

#include "install/IInstallService.h"

#include <string>

namespace udc {

struct PackageUpdate;

class IDownloadService {
  public:
    virtual ~IDownloadService() = default;
    virtual LocalArchiveInfo download(PackageUpdate package,
                                      const std::string& destDir) = 0;
};

} // namespace udc

#endif //IDOWNLOADSERVICE_H
