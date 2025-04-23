//
// Created by horeb on 25-4-17.
//

#ifndef IUPDATEPROVIDER_H
#define IUPDATEPROVIDER_H

#include "model/UpdatesXML.h"

#include <string>

namespace udc {

// IUpdateProvider  (interface)
// ├─ fetch() : string                  ← 拉取原始 Updates.xml 文本
// └─ parse(xml: string) : Updates      ← 解析成 Updates 对象
//
//   │
//   ├─ XmlUpdateProvider (implements)  ← 从 HTTP 或本地文件下载 XML
//   └─ MockUpdateProvider (implements) ← 单元测试用，提供本地模拟 XML

class IUpdateProvider {
public:
    virtual ~IUpdateProvider() = default;

    virtual std::string fetch() = 0;
    virtual Updates parse(const std::string& xml) = 0;

};

}

#endif //IUPDATEPROVIDER_H
