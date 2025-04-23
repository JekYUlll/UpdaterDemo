//
// Created by horeb on 25-4-16.
//

#ifndef MODEL_UPDATES_XML_H
#define MODEL_UPDATES_XML_H

#include "model/Date.h"
#include "model/Version.h"

#include <string>
#include <vector>

namespace udc {

/**
 * @struct PackageUpdate
 * @brief 对应Updates.xml里的<PackageUpdate>
 */
struct PackageUpdate {
    std::string name;                 // xml: Name
    std::string displayName;          // xml: DisplayName
    std::string description;          // xml: Description
    Version version;                  // xml: Version
    std::string releaseDate;          // xml: ReleaseDate
    bool isDefault = false;           // xml: Default
    bool isVirtual = false;           // xml: Virtual
    std::string downloadableArchives; // xml: DownloadableArchives
    std::string sha1;                 // xml: SHA1
    struct {
        std::string os;
        int compressedSize = 0;
        int uncompressedSize = 0;
    } updateFile; // xml: UpdateFile
};

/**
 * @struct Updates
 * @brief 最外层，对应Updates.xml
 */
struct Updates {
    std::string applicationName;         // xml: ApplicationName
    Version applicationVersion;          // xml: ApplicationVersion
    bool bChecksum = false;              // xml: Checksum
    std::vector<PackageUpdate> packages; // xml: Packages
};

/**
 * @struct PackageMeta
 * @brief 对应组件元信息：package.xml <Package>
 */
struct PackageMeta {
    std::string displayName;               // xml: DisplayName
    std::string description;               // xml: Description
    Version version;                       // xml: Version
    Date releaseDate;                      // xml: ReleaseDate
    bool isDefault = false;                // xml: Default
    bool isVirtual = false;                // xml: Virtual
    std::string script;                    // xml: Script
    std::vector<std::string> dependencies; // xml: Dependencies
};

typedef PackageMeta Package;

}

#endif //MODEL_UPDATES_XML_H
