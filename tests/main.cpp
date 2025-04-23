//
// Created by horeb on 25-4-19.
//
#include <string>

#include "core/UpdateManager.h"
#include "download/HttpDownloadService.h"
#include "install/ZipInstallService.h"
#include "local/XmlComponentRepository.h"
#include "net/HttpNetworkAccess.h"
#include "provider/XmlUpdateProvider.h"
#include "selector/UpdateSelector.h"

const std::string REPO_URL = "http://127.0.0.1:8090/repo/";

using namespace udc;

int main(int argc, char* argv[]) {

    // TODO:
    // 1. 多次传递REPO_URL。应该将其抽象为一个表达远程仓库的类；

    XmlComponentRepository localRepo("components.xml");

    const auto netAccess = std::make_shared<HttpNetworkAccess>();

    HttpDownloadService downloader(REPO_URL, netAccess);

    XmlUpdateProvider updateProvider(REPO_URL, netAccess);

    UpdateSelector selector;

    ZipInstallService installer;

    UpdateManager manager(localRepo, updateProvider, selector, downloader,
                          installer, REPO_URL);

    auto result = manager.installAll(
        manager.checkAndDownload("1.0.0-beta1", "./downloads/1.0.0-beta1"), "./installs/1.0.0-beta1");

    return 0;
}
