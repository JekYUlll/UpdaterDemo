# selector

业务决策层（Selection），封装「哪些组件要更新」的决策逻辑。

从[provider](../provider/readme.md)层解析的`Updates`中获取一系列`PackageUpdate`，传递给[download](../download/readme.md)层。

```txt
UpdateSelector
└─ select(updates: Updates, currentVersion: Version) : List<PackageUpdate>
     • 根据策略（默认/版本号/平台/用户选择）筛选出需要下载的 PackageUpdate
     列表
```