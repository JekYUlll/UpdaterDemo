//
// Created by horeb on 25-4-19.
//

#ifndef ICOMPONENTREPOSITORY_H
#define ICOMPONENTREPOSITORY_H

#include "model/ComponentsXML.h"

namespace udc {

class IComponentRepository {
  public:
    virtual ~IComponentRepository() = default;

    // 从 components.xml 加载本地已安装的组件列表
    virtual Components load() = 0;

    // 将修改后的组件列表写回 components.xml
    virtual void save(const Components& comps) = 0;
};
}

#endif //ICOMPONENTREPOSITORY_H
