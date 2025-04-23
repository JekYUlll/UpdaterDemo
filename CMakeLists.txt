cmake_minimum_required(VERSION 3.28)

project(UpdaterDemoCpp
        VERSION 1.0
        DESCRIPTION "Updater Demo"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/third_party
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(third_party/tinyxml2)
add_subdirectory(third_party/cpr)
add_subdirectory(third_party/spdlog)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")
set(CMAKE_TLS_VERIFY false)

add_executable(UpdaterDemoCpp tests/main.cpp
        include/core/UpdateManager.h
        include/model/UpdatesXML.h
        include/provider/IUpdateProvider.h
        include/install/IInstallService.h
        include/common/Path.h
        include/download/IDownloadService.h
        include/download/MockDownloadService.h
        include/download/HttpDownloadService.h
        include/provider/XmlUpdateProvider.h
        include/provider/MockUpdateProvider.h
        include/selector/UpdateSelector.h
        include/net/INetworkAccess.h
        include/net/HttpNetworkAccess.h
        include/install/ZipInstallService.h
        include/install/RsyncInstallService.h
        include/install/MockInstallService.h
        include/model/LocalArchiveInfo.h
        include/model/Version.h
        include/model/Date.h
        include/model/ComponentsXML.h
        include/model/Repository.h
        include/model/Config.h
        include/log/Logger.h
        include/selector/UpdateSelector.h
        include/selector/MockSelector.h
        include/selector/IPackageSelector.h
        include/local/IComponentRepository.h
        include/local/XmlComponentRepository.h
        include/local/MockComponentRepository.h
        include/error/exception.h
        include/config/IConfigLoader.h
        include/config/XMLConfigLoader.h
)

target_link_libraries(UpdaterDemoCpp PRIVATE
        tinyxml2::tinyxml2
        cpr::cpr
        spdlog::spdlog_header_only
)
