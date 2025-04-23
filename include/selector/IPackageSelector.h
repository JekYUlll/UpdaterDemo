//
// Created by horeb on 25-4-17.
//

#ifndef UDC_I_PACKAGESELECTOR_H
#define UDC_I_PACKAGESELECTOR_H

#include <vector>

namespace udc {

struct Version;
struct Updates;
struct PackageUpdate;

/**
 * @class IPackageSelector
 */
class IPackageSelector {
  public:
    IPackageSelector() = default;
    virtual ~IPackageSelector() = default;

    virtual std::vector<PackageUpdate> select(Updates& updates, const Version& currentVersion) = 0;
};


}

#endif //UDC_I_PACKAGESELECTOR_H
