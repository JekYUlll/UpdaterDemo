//
// Created by horeb on 25-4-17.
//

#ifndef IINSTALLSERVICE_H
#define IINSTALLSERVICE_H

#include "model/UpdatesXML.h"

#include <filesystem>
#include <optional>
#include <string>
#include <utility>

namespace udc {

struct LocalArchiveInfo;

enum class InstallStatus {
    Success,
    FileCorrupted,
    ExtractionFailed,
    InvalidFormat,
    TargetDirectoryError,
    AlreadyInstalled,
    UnknownError
};

struct InstallResult {
    InstallStatus status;
    std::string message; // 用于日志、调试、用户提示
    std::optional<std::string> installedPath; // 安装成功后返回路径
    std::optional<std::string> failedFile; // 指出失败的文件（用于错误详情）

    static InstallResult success(const std::string& path) {
        return {InstallStatus::Success, "Install succeeded.", path,
                std::nullopt};
    }

    static InstallResult
    failure(const InstallStatus code, const std::string& msg,
            std::optional<std::string> file = std::nullopt) {
        return {code, msg, std::nullopt, std::move(file) };
    }
};

class IInstallService {

  public:
    virtual ~IInstallService() = default;

    virtual InstallResult install(const LocalArchiveInfo& archive,
                                  const std::string& targetDir) = 0;
};

}

#endif //IINSTALLSERVICE_H
