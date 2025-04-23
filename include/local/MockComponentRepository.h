//
// Created by horeb on 25-4-19.
//

#ifndef MOCKCOMPONENTREPOSITORY_H
#define MOCKCOMPONENTREPOSITORY_H

#include "local/IComponentRepository.h"
#include "log/Logger.h"

namespace udc {

class MockComponentRepository final : public IComponentRepository {
  public:
    MockComponentRepository() = default;

    ~MockComponentRepository() override = default;

    Components load() override {
        LOG_D("MockComponentRepository::load");
        return Components{};
    }

    void save(const Components& comps) override {
        LOG_D("MockComponentRepository::save");
    }
};

} // namespace udc

#endif // MOCKCOMPONENTREPOSITORY_H
