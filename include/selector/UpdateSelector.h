//
// Created by horeb on 25-4-19.
//
#pragma once
#ifndef UDC_UPDATESELECTOR_H
#define UDC_UPDATESELECTOR_H

#include "model/UpdatesXML.h"
#include "selector/IPackageSelector.h"

#include <string>
#include <vector>

namespace udc {

class UpdateSelector final : public IPackageSelector {
  public:
    UpdateSelector() = default;

    explicit UpdateSelector(const std::string& configPath) { (void)configPath; }

    ~UpdateSelector() override = default;

    std::vector<PackageUpdate> select(Updates& updates,
                                      const Version& currentVersion) override {
        return {};
    }
};

} // namespace udc

#endif // UDC_UPDATESELECTOR_H
