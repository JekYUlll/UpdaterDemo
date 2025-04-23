//
// Created by horeb on 25-4-18.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "model/Date.h"
#include "model/Version.h"

#include <string>
#include <vector>

namespace udc {

/**
 * @struct LocalPackage
 * @brief 本地components.xml中的<Packages>
 */
struct LocalPackage {
    std::string name;        // xml: Name
    std::string title;       // xml: Title
    std::string description; // xml: Description
    Version version;         // xml: Version
    Date lastUpdateDate;     // xml: LastUpdateDate
    Date installDate;        // xml: InstallDate
    int size;                // xml: Size
    bool checkable;          // xml: Checkable
};

/**
 * @struct LocalPackages
 * @brief 对应整个components.xml
 */
struct LocalPackages {
    std::string applicationName;        // xml: ApplicationName
    Version applicationVersion;         // xml: ApplicationVersion
    std::vector<LocalPackage> packages; // xml: Packages
};

typedef LocalPackage Component;
typedef LocalPackages Components;

} // namespace udc

#endif //COMPONENTS_H
