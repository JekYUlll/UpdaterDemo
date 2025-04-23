//
// Created by horeb on 25-4-18.
//

#ifndef LOCALARCHIVEINFO_H
#define LOCALARCHIVEINFO_H

#include "model/Version.h"

#include <bits/fs_path.h>

namespace udc {

struct LocalArchiveInfo {
    std::filesystem::__cxx11::path localPath; // 下载后的完整路径
    std::string sha1;            // 校验用（从 metadata 中带过来）
    size_t compressedSize = 0;   // 实际下载后的大小（字节）
    size_t uncompressedSize = 0; // 预期解压后大小（可选）

    std::string archiveName; // 如 content.7z（可选）
    std::string packageName; // 属于哪个组件，如 "A"（可选）
    Version version;

    bool isValid = false; // 下载后是否校验通过

    bool verifySha1() {
        // todo 加上实际的 SHA1 校验逻辑
        isValid = true;
        return true;
    }
};

}

#endif //LOCALARCHIVEINFO_H
