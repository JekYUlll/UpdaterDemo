//
// Created by horeb on 25-4-18.
//

#ifndef HTTPDOWNLOADSERVICE_H
#define HTTPDOWNLOADSERVICE_H

#include "download/IDownloadService.h"
#include "model/LocalArchiveInfo.h"
#include "net/INetworkAccess.h"

#include <utility>

namespace fs = std::filesystem;

namespace udc {

class HttpDownloadService final : public IDownloadService {
  public:
    HttpDownloadService(const std::string_view repoUrl,
                        const std::shared_ptr<INetworkAccess>& networkAccess)
        : m_repoUrl(repoUrl), m_net(networkAccess) {}

    ~HttpDownloadService() override = default;

    LocalArchiveInfo download(PackageUpdate package,
                              const std::string& destDir) override {
        const std::string& archiveFileName = package.downloadableArchives;
        const std::string& componentName = package.name;
        const std::string& version = package.version.toString();
        // 拼接 URL：repoUrl/component/version/content.7z
        std::ostringstream urlBuilder;
        urlBuilder << m_repoUrl;
        if (m_repoUrl.back() != '/') urlBuilder << '/';
        urlBuilder << componentName << '/' << version << '/' << archiveFileName;
        std::string archiveUrl = urlBuilder.str();
        // 拼接本地路径
        fs::path destPath = fs::path(destDir) / componentName / version;
        fs::create_directories(destPath);
        fs::path localArchivePath = destPath / archiveFileName;
        // 下载文件
        if (!m_net->downloadToFile(archiveUrl, localArchivePath.string())) {
            throw std::runtime_error("Download failed for: " + archiveUrl);
        }
        // todo 填充 LocalArchiveInfo
        LocalArchiveInfo info{};
        // info.localPath = localArchivePath.string();
        // info.package = package;

        return info;
    }

  private:
    std::string m_repoUrl;
    std::shared_ptr<INetworkAccess> m_net;
};

} // namespace udc

#endif // HTTPDOWNLOADSERVICE_H
