//
// Created by horeb on 25-4-16.
//

#ifndef MODEL_UPDATES_H
#define MODEL_UPDATES_H

#include <string>

/**
 * @struct PackageUpdate
 * @brief 对应Updates.xml里的：
*       <PackageUpdate>
            <Name>A</Name>
            <DisplayName>A</DisplayName>
            <Description>Example component A</Description>
            <Version>1.0.2-1</Version>
            <ReleaseDate>2015-01-01</ReleaseDate>
            <Default>true</Default>
            <UpdateFile CompressedSize="222" OS="Any" UncompressedSize="72"/>
            <DownloadableArchives>content.7z</DownloadableArchives>
            <SHA1>9d54e3a5adf3563913feee8ba23a99fb80d46590</SHA1>
        </PackageUpdate>
 */
struct PackageUpdate {
    std::string Name;
    std::string DisplayName;
    std::string Description;
    std::string Version;
    std::string ReleaseDate;
    bool Default = false;
    bool Virtual = false;
    std::string DownloadableArchives; // 对应文件名
    std::string SHA1;
    struct {
        std::string os;
        int compressedSize = 0;
        int uncompressedSize = 0;
    } UpdateFile;
};

/**
 * @struct PackageMeta
 * @brief 对应组件元信息：package.xml
 * <Package>
        <DisplayName>A</DisplayName>
        <Description>Example component A</Description>
        <Version>1.0.0</Version>
        <ReleaseDate>2020-01-01</ReleaseDate>
        <Default>true</Default>
        <Script>script1.0.0.qs</Script>
    </Package>
 */
struct PackageMeta {
    std::string DisplayName;
    std::string Description;
    std::string Version;
    std::string ReleaseDate;
    bool Default = false;
    bool Virtual = false;
    std::string Script;
};

/*
struct PackageVersion {
    int major;
    int minor;
    int patch;
    [[nodiscard]] std::string toString() const {
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }
};*/

#endif //MODEL_UPDATES_H
