# download

接收[selector](../selector/readme.md)层传递的`PackageUpdate`，进行下载行为。  
下载的内容在本地记录为`LocalArchiveInfo`，传递给[install](../install/readme.md)层。

```txt
IDownloadService  (interface)
└─ download(pkg: PackageUpdate, destDir: string) : LocalArchiveInfo

│
└─ HttpDownloadService (implements)
• 使用 libcurl 或 httplib 下载内容
```

仓库拉取职责：
```txt
+------------------------+             +-----------------------------+
|    IUpdateProvider     | fetch()     |      Updates.xml 文件内容    |
| (如 XmlUpdateProvider) +-----------> | http://.../Updates.xml       |
|                        | parse()     | -> Updates 数据结构          |
+------------------------+             +-----------------------------+

        │                                      │
        ▼                                      ▼

+------------------------+             +------------------------------+
|  HttpDownloadService   | download()  |  下载 content.7z 和校验 .sha1 |
+------------------------+<----------->| http://.../componentX/...     |
```