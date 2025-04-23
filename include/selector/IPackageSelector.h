//
// Created by horeb on 25-4-17.
//

#ifndef UPDATESELECTOR_H
#define UPDATESELECTOR_H

#include <vector>

namespace udc {

struct Version;
struct Updates;
struct PackageUpdate;

class IPackageSelector {

  public:
    IPackageSelector() = default;
    virtual ~IPackageSelector() = default;

    virtual std::vector<PackageUpdate>
    select(Updates& updates, const Version& currentVersion) = 0;
};


}

#endif //UPDATESELECTOR_H
