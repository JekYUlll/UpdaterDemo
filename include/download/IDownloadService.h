//
// Created by horeb on 25-4-17.
//

#ifndef IDOWNLOADSERVICE_H
#define IDOWNLOADSERVICE_H

#include "IInstallService.h"

#include <string>

namespace udc {

struct PackageUpdate;

/*IDownloadService  (interface)
└─ download(pkg: PackageUpdate, destDir: string) : LocalArchiveInfo

  │
  └─ HttpDownloadService (implements)
       • 使用 libcurl 或 httplib 下载内容*/

class IDownloadService {
  public:
    virtual ~IDownloadService() = default;
    virtual LocalArchiveInfo download(PackageUpdate package,
                                      const std::string& destDir) = 0;
};

} // namespace udc

#endif //IDOWNLOADSERVICE_H
