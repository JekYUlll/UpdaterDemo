# QtIFW的安装包的构建

[//]: # (2025-04-19)

- [Creating Online Installers](https://doc.qt.io/qtinstallerframework/ifw-online-installers.html)

安装程序配置文件 `config.xml`:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Installer>
    <Name>Online Installer Example</Name>
    <Version>1.0.0</Version>
    <Title>Online Installer Example</Title>
    <Publisher>The Qt Company</Publisher>
    <!-- Directory name is used in component.xml -->
    <StartMenuDir>Qt IFW Examples</StartMenuDir>
    <TargetDir>@HomeDir@/IfwExamples/online</TargetDir>
    <RemoteRepositories>
        <Repository>
            <Url>http://localhost/repository</Url>
        </Repository>
    </RemoteRepositories>
</Installer>
```

- 完整配置：[Configuration File](https://doc.qt.io/qtinstallerframework/ifw-globalconfig.html)。


---

### 1. 服务端 - 远程存储库配置

使用`repogen`工具创建一个包目录的所有包的在线存储库：
```bash
repogen.exe -p < 软件包目录> < 存储库目录>
```
例如，要创建仅包含 `org.qt-project.sdk.qt` 和 `org.qt-project.sdk.qtcreator` 的存储库：
```bash
repogen.exe -p packages -i org.qt-project.sdk.qt,org.qt-project.sdk.qtcreator repository
```

**配置存储库**：

`config.xml` 中的 `<RepositoryCategory>` 元素可以包含多个 `<RemoteRepositories>` 元素的列表：

```xml
<RepositoryCategories>
    <RemoteRepositories>
         <Displayname>Category 1</Displayname>
         <Preselected>true</Preselected>
         <Tooltip>Tooltip for category 1</Tooltip>
         <Repository>
                 <Url>http://www.example.com/packages</Url>
                 <Enabled>1</Enabled>
                 <Username>user</Username>
                 <Password>password</Password>
                 <DisplayName>Example repository</DisplayName>
         </Repository>
    </RemoteRepositories>
</RepositoryCategories>
```

`<RemoteRepositories>` 元素可以包含多个存储库的列表：

```xml
<RemoteRepositories>
     <Repository>
             <Url>http://www.example.com/packages</Url>
             <Enabled>1</Enabled>
             <Username>user</Username>
             <Password>password</Password>
             <DisplayName>Example repository</DisplayName>
     </Repository>
</RemoteRepositories>
```

- `<Username>` ，用作受保护存储库上的用户。  
- `<DisplayName>` ，可选择设置要显示的字符串而不是 URL。

---

### 2. 创建安装程序二进制文件

使用 `binarycreator` 工具创建在线安装程序：

```bash
<location-of-ifw>\binarycreator.exe -t <location-of-ifw>\installerbase.exe -p <package_directory> -c <config_directory>\<config_file> -e <packages> <installer_name>
```

例如，输入以下命令来创建名为 `SDKInstaller.exe` 的安装程序二进制文件，该文件将不包含 `org.qt-project.sdk.qt` 和 `org.qt-project.qtcreator` 的数据，因为这些包是从远程存储库下载的：

```bash
binarycreator.exe -p installer-packages -c installer-config\config.xml -e org.qt-project.sdk.qt,org.qt-project.qtcreator SDKInstaller.exe
```

> 即使组件是从 Web 服务器获取的， binarycreator 也会默认将其添加到安装程序二进制文件中。

> 可以创建不包含任何数据并从 Web 服务器获取所有数据的在线安装程序。  
> 使用 `binarycreator` 工具的 `-n` 参数，并仅将根组件添加到安装程序中。通常根组件为空，因此仅添加根组件的 XML 描述。






