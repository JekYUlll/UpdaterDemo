
完整更新逻辑：  
本地的`components.xml`里存储本地的包信息。  
从服务端获取`Updates.xml`，对应的包名路径下有压缩后的元信息（主要内容为`package.xml`）。

`Updates.xml`:
```xml
<Updates>
    <ApplicationName>{AnyApplication}</ApplicationName>
    <ApplicationVersion>1.0.0</ApplicationVersion>
    <Checksum>true</Checksum>
    <PackageUpdate>
        <Name>A</Name>
        <DisplayName>A</DisplayName>
        <Description>Example component A</Description>
        <Version>1.0.2-1</Version>
        <ReleaseDate>2015-01-01</ReleaseDate>
        <Default>true</Default>
        <UpdateFile CompressedSize="222" OS="Any" UncompressedSize="72"/>
        <DownloadableArchives>content.7z</DownloadableArchives>
        <SHA1>9d54e3a5adf3563913feee8ba23a99fb80d46590</SHA1>
    </PackageUpdate>
    <PackageUpdate>
        <Name>B</Name>
        <DisplayName>B</DisplayName>
        <Description>Example component B</Description>
        <Version>1.0.0-1</Version>
        <ReleaseDate>2015-01-01</ReleaseDate>
        <Default>false</Default>
        <UpdateFile CompressedSize="222" OS="Any" UncompressedSize="72"/>
        <DownloadableArchives>content.7z</DownloadableArchives>
        <SHA1>9170d55a6af81c1a6a63d708a4ab6ed359775cd9</SHA1>
    </PackageUpdate>
    <PackageUpdate>
        <Name>C</Name>
        <DisplayName>C</DisplayName>
        <Description>Example component C</Description>
        <Version>1.0.0-1</Version>
        <ReleaseDate>2015-01-01</ReleaseDate>
        <Default>true</Default>
        <UpdateFile CompressedSize="222" OS="Any" UncompressedSize="72"/>
        <DownloadableArchives>content.7z</DownloadableArchives>
        <SHA1>5b3939da1af492382c68388fc796837e4c36b876</SHA1>
    </PackageUpdate>
    <PackageUpdate>
        <Name>C.virt</Name>
        <DisplayName>Virtual subcomponent of C</DisplayName>
        <Description>Example virtual component</Description>
        <Version>1.0.0-1</Version>
        <ReleaseDate>2015-01-01</ReleaseDate>
        <Virtual>true</Virtual>
        <UpdateFile CompressedSize="222" OS="Any" UncompressedSize="72"/>
        <DownloadableArchives>content.7z</DownloadableArchives>
        <SHA1>5b3939da1af492382c68388fc796837e4c36b876</SHA1>
    </PackageUpdate>
    <PackageUpdate>
        <Name>C.virt.subcomponent</Name>
        <DisplayName>Subcomponent of virtual component</DisplayName>
        <Description>Example subcomponent of virtual component</Description>
        <Version>1.0.0-1</Version>
        <ReleaseDate>2015-01-01</ReleaseDate>
        <UpdateFile CompressedSize="222" OS="Any" UncompressedSize="72"/>
        <DownloadableArchives>content.7z</DownloadableArchives>
        <SHA1>5b3939da1af492382c68388fc796837e4c36b876</SHA1>
    </PackageUpdate>
    <PackageUpdate>
        <Name>AB</Name>
        <DisplayName>AB</DisplayName>
        <Description>Example component AB</Description>
        <Version>1.0.2-1</Version>
        <ReleaseDate>2015-01-01</ReleaseDate>
        <Default>true</Default>
        <UpdateFile UncompressedSize="0" OS="Any" CompressedSize="0"/>
        <SHA1>f75e65b1a0f68abb77fc41da08fc26dda5409a18</SHA1>
    </PackageUpdate>
</Updates>
```

`components.xml`:
```xml
<Packages>
    <ApplicationName>Online Installer Example</ApplicationName>
    <ApplicationVersion>1.0.0</ApplicationVersion>
    <Package>
        <Name>A</Name>
        <Title>A Title</Title>
        <Description>Example component A</Description>
        <Version>1.0.2-1</Version>
        <LastUpdateDate></LastUpdateDate>
        <InstallDate>2020-02-13</InstallDate>
        <Size>74</Size>
        <Checkable>true</Checkable>
    </Package>
    <Package>
        <Name>B</Name>
        <Title>B Title</Title>
        <Description>Example component B</Description>
        <Version>1.0.0-1</Version>
        <LastUpdateDate></LastUpdateDate>
        <InstallDate>2020-02-13</InstallDate>
        <Size>74</Size>
        <Checkable>true</Checkable>
    </Package>
</Packages>
```

`package.xml`:
```xml
<?xml version="1.0" encoding="UTF-8"?>
<Package>
    <DisplayName>A</DisplayName>
    <Description>Example component A</Description>
    <Version>1.0.0</Version>
    <ReleaseDate>2020-01-01</ReleaseDate>
    <Default>true</Default>
    <Script>script1.0.0.qs</Script>
</Package>
```

`Updates.xml`  
- 位置：存在于服务端存储库的根目录
- 作用：提供所有可用包的版本信息和元数据位置
- 处理时机：在检查更新或获取可安装组件列表时

`package.xml`  
- 位置：位于每个组件的meta目录中，如`[component]/meta/package.xml`
- 作用：提供单个组件的详细描述和配置
- 处理时机：构建安装包时和加载组件详细信息时