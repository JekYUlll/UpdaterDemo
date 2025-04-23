//
// Created by horeb on 25-4-21.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <string>

namespace udc {

/**
 * @struct Repository
 * @brief [config.xml]<Repository>
 */
struct Repository {
    std::string url;         // xml: Url
    bool enabled = true;     // xml: Enabled
    std::string username;    // xml: Username
    std::string password;    // xml: Password
    std::string displayName; // xml: DisplayName
};

} // namespace udc

#endif // REPOSITORY_H
