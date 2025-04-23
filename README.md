todo：组件的结构是否需要抽象为图？有父子组件。

namespace KDUpdater {
class KDTOOLS_EXPORT UpdateFinder : public Task
{
public:
QList<Update *> updates() const;
void setLocalPackageHub(std::weak_ptr<LocalPackageHub> hub);
void setPackageSources(const QSet<QInstaller::PackageSource> &sources);

private:
bool downloadUpdateXMLFiles();
bool parseUpdateXMLFiles();
bool removeInvalidObjects();
bool computeApplicableUpdates();
QList<UpdateInfo> applicableUpdates(UpdatesInfo *updatesInfo);
Resolution checkPriorityAndVersion(const QInstaller::PackageSource &source, const QVariantHash &data) const;
};
}

int KDUpdater::compareVersion(const QString &v1, const QString &v2);

## 1. 核心模型层（Data Model）

```text
Updates                    —───► contains 0..* PackageUpdate
└─ PackageUpdate
     • name: string
     • version: Version
     • releaseDate: Date
     • default: bool
     • virtual: bool
     • archives: string[]
     • sha1: string
     • updateFile: UpdateFileMeta

└─ UpdateFileMeta
     • os: string
     • compressedSize: int
     • uncompressedSize: int
```

---

## 2. 解析/检测层（Check & Parse）

```text
IUpdateProvider  (interface)
├─ fetch() : string                  ← 拉取原始 Updates.xml 文本
└─ parse(xml: string) : Updates      ← 解析成 Updates 对象

  │
  ├─ XmlUpdateProvider (implements)  ← 从 HTTP 或本地文件下载 XML
  └─ MockUpdateProvider (implements) ← 单元测试用，提供本地模拟 XML
```

- **职责**：
    1. `fetch()` 拿到原始文本（可选 HTTP 或本地）；
    2. `parse()` 调用 tinyxml2 把文本转成模型。

---

## 3. 业务决策层（Selection）

```text
UpdateSelector
└─ select(updates: Updates, currentVersion: Version) : List<PackageUpdate>
     • 根据策略（默认/版本号/平台/用户选择）筛选出需要下载的 PackageUpdate 列表
```

- **职责**：封装「哪些组件要更新」的决策逻辑。

---

## 4. 下载/安装共用层（Download & Install 抽象）

#### 4.1. 下载接口

```text
IDownloadService  (interface)
└─ download(pkg: PackageUpdate, destDir: string) : LocalArchiveInfo

  │
  └─ HttpDownloadService (implements)
       • 使用 libcurl 或 httplib 下载内容
```

- **`LocalArchiveInfo`**：封装下载后本地文件路径、大小、校验信息等。

#### 4.2. 安装接口

```text
IInstallService   (interface)
└─ install(archive: LocalArchiveInfo, targetDir: string) : InstallResult

  │
  ├─ ZipInstallService    (implements)  ← 解压 .7z/.zip
  └─ RsyncInstallService  (implements)  ← 文件直接覆盖（示例）
```

- **职责**：把下载到的压缩包或资源应用到目标路径，不管它来源于“更新”还是“在线安装”都可用。

---

## 5. 协调层（Orchestration）

```text
UpdateManager
├─ provider: IUpdateProvider
├─ selector: UpdateSelector
├─ downloader: IDownloadService
├─ installer: IInstallService

└─ checkAndDownload(currentVersion: Version, downloadDir: string)
     1. xmlText ← provider.fetch()
     2. updates ← provider.parse(xmlText)
     3. toUpdateList ← selector.select(updates, currentVersion)
     4. for each pkg in toUpdateList:
          localInfo ← downloader.download(pkg, downloadDir)
     5. return List<LocalArchiveInfo>

└─ installAll(archives: List<LocalArchiveInfo>, targetDir: string)
     for each arc in archives:
       installer.install(arc, targetDir)
```

- **职责**：
    - `checkAndDownload` 只管“检测+下载”，不触碰安装；
    - `installAll` 只管“安装”，不触碰检测逻辑。
    - 真正的更新流程：
      ```cpp
      auto archives = mgr.checkAndDownload(curVer, "/tmp/updates");
      mgr.installAll(archives, "/app/path");
      ```