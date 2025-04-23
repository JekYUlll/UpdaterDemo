# install

接收[download](../download/readme.md)层返回的`LocalArchiveInfo`，进行安装。

```txt
IInstallService   (interface)
└─ install(archive: LocalArchiveInfo, targetDir: string) : InstallResult

  │
  ├─ ZipInstallService    (implements)  ← 解压 .7z/.zip
  └─ RsyncInstallService  (implements)  ← 文件直接覆盖（示例）
```