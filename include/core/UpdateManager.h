//
// Created by horeb on 25-4-17.
//

#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include "download/IDownloadService.h"
#include "download/MockDownloadService.h"
#include "install/MockInstallService.h"
#include "local/MockComponentRepository.h"
#include "provider/IUpdateProvider.h"
#include "provider/MockUpdateProvider.h"
#include "selector/IPackageSelector.h"
#include "selector/MockSelector.h"

namespace udc {

class IComponentRepository;
class UpdateSelector;
class IPackageSelector;
struct LocalPackage;

class UpdateManager {
  public:
    template <typename... URLS>
    UpdateManager(IComponentRepository& compRepo, IUpdateProvider& updProv,
                  IPackageSelector& selector, IDownloadService& downloader,
                  IInstallService& installer, URLS&&... urls)
        : m_compRepo(compRepo), m_provider(updProv), m_selector(selector),
          m_downloader(downloader), m_installer(installer),
          m_repoUrls{std::forward<URLS>(urls)...} {}

    ~UpdateManager() = default;

    UpdateManager(const UpdateManager&) = delete;

    [[nodiscard]] std::vector<LocalArchiveInfo>
    checkAndDownload(const Version& currentVersion,
                     const std::string& downloadDir) const {
        const std::string xmlText = m_provider.fetch();
        auto updates = m_provider.parse(xmlText);
        auto toUpdateList = m_selector.select(updates, currentVersion);
        std::vector<LocalArchiveInfo> result;
        for (const auto& pkg : toUpdateList) {
            auto localInfo = m_downloader.download(pkg, downloadDir);
            result.push_back(localInfo);
        }
        return result;
    }

    [[nodiscard]] InstallResult
    installAll(const std::vector<LocalArchiveInfo>& archives,
               const std::string& targetDir) const {
        for (auto& arc : archives) {
            m_installer.install(arc, targetDir);
        }
        return InstallResult::success(targetDir);
    }

    struct MockContext {

        MockComponentRepository localRepo;
        MockUpdateProvider updateProvider;
        MockDownloadService downloadService;
        MockInstallService installService;
        MockSelector selector;

        std::unique_ptr<UpdateManager> createManager() {
            return std::make_unique<UpdateManager>(
                localRepo, updateProvider, selector, downloadService,
                installService, "mock://repo");
        }
    };

  private:
    IComponentRepository& m_compRepo;
    IUpdateProvider& m_provider;
    IPackageSelector& m_selector;
    IDownloadService& m_downloader;
    IInstallService& m_installer;

    typedef std::string RepoUrl;
    std::vector<RepoUrl> m_repoUrls;
};

} // namespace udc

#endif // UPDATEMANAGER_H
