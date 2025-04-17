cmake_minimum_required(VERSION 3.28)
project(UpdaterDemoCpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        include/
        third_party/
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(third_party/tinyxml2)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")

add_executable(UpdaterDemoCpp src/main.cpp
        include/updater.h
        include/serialize.h
        include/model.h
        include/config.h)

target_link_libraries(UpdaterDemoCpp PRIVATE tinyxml2::tinyxml2)
