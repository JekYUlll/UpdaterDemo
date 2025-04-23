# core

```txt
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