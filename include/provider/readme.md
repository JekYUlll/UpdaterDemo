# provider

解析/检测层（Check & Parse）。

从仓库 url 获取 Updates.xml，从中解析出元信息。

```txt
IUpdateProvider  (interface)
├─ fetch() : string                  ← 拉取原始 Updates.xml 文本
└─ parse(xml: string) : Updates      ← 解析成 Updates 对象

  │
  ├─ XmlUpdateProvider (implements)  ← 从 HTTP 或本地文件下载 XML
  └─ MockUpdateProvider (implements) ← 单元测试用，提供本地模拟 XML
```