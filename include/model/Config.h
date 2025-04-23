//
// Created by horeb on 25-4-21.
//

#ifndef CONFIG_H
#define CONFIG_H

#include "Version.h"

#include <string>
#include <vector>

namespace udc {

struct Repository;
struct Version;

/**
 * @struct Config
 * @brief [config.xml]
 */
struct Config {
    std::string name;                     // xml: Name
    Version version;                      // xml: Version
    std::string targetDir;                // xml: TargetDir
    std::vector<Repository> repositories; // xml: Repositories
};

} // namespace udc

#endif // CONFIG_H
