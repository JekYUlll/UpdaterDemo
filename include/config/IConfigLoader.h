//
// Created by horeb on 25-4-21.
//

#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include "model/Config.h"

namespace udc {

class IConfigLoader {
public:
    virtual ~IConfigLoader() = default;

    virtual Config loadFromFile(const std::string& path) = 0;
};

}

#endif // CONFIGLOADER_H
