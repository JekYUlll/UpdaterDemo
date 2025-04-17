//
// Created by horeb on 25-4-16.
//

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "tinyxml2.h"

/*
QtIfw:
3. 如何获取更新信息？
- 获取远端的`Updates.xml`，每个组件的详细信息为`package.xml`。
4. 如何存储本地的版本号信息？
- 在安装目录下保存一个名为`components.xml`的文件（可通过配置自定义名称）。
*/

/*
 *
 *思考，直接对比各个组件，还是对比版本号？版本号不同的时候，获取变化的组件信息
 *
 *信息流：解析本地components.xml，获取本地各组件版本信息(std::vector<PackageInfo>)
 *        发送请求，申请服务端Updates.xml -> 解析为UpdateInfo -> 与本地对比
 *        -> 获取到需要更新的包(无需对用户可见) -> 发送请求，申请每个包对应的package.xml
 *        -> 解析package.xml为PackageInfo -> 从中获取资源url -> 下载
 *        -> 安装
 *
Updates                    —───► contains 0..* PackageUpdate
└─ PackageUpdate
     • name: string
     • version: Version
     • releaseDate: Date
     • default: bool
     • virtual: bool
     • archives: string[]
     • sha1: string
     • updateFile: UpdateFileMeta

└─ UpdateFileMeta
     • os: string
     • compressedSize: int
     • uncompressedSize: int
 *
*/

struct Url {
    std::string url;
};

struct PackageVersion {
    int major;
    int minor;
    int patch;
    [[nodiscard]] std::string String() const {
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }
};

struct PackageInfo {
    int id;
    std::string name;
    std::string description;
    PackageVersion version;
    [[nodiscard]] std::string Version() const {
        return version.String();
    }
};

struct UpdateInfo {
  int id;
  tinyxml2::XMLElement* xml;
  std::vector<PackageInfo> list;
};

 enum class UpdateStatus {
  NoUpdate,          // 无可用更新
  UpdateAvailable,   // 有更新
  NetworkError,      // 网络错误
  ParseError,        // XML解析失败
  InvalidVersion     // 版本格式无效
};

 struct CheckUpdateResult {
  UpdateStatus status;   // 更新状态
  std::string latestVersion;  // 服务器最新版本号
  std::string updateUrl;      // 更新包URL
  std::string description;    // 更新说明
  bool forceUpdate;       // 是否强制更新
 };

#endif //MODEL_H
