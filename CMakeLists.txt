cmake_minimum_required(VERSION 3.10)

project(RoPP VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

set(SOURCE_FILES
    source/helper.cpp
    source/group.cpp
    source/avatar.cpp
    source/asset.cpp
    source/trade.cpp
    source/auth.cpp
    source/user.cpp
    source/session.cpp
    source/other.cpp
    source/game.cpp
    source/chat.cpp
)

add_library(ropp ${SOURCE_FILES})

target_include_directories(ropp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/RoPP>
)

find_package(CURL REQUIRED)

target_link_libraries(ropp PRIVATE CURL::libcurl)

include(GNUInstallDirs)

install(TARGETS ropp
    EXPORT RoPP-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/RoPP)

install(EXPORT RoPP-targets
    FILE RoPPTargets.cmake
    NAMESPACE RoPP::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/RoPP
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/RoPPTargets.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/RoPP
    COMPONENT Devel
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/RoPPConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/RoPPConfig.cmake"
    @ONLY
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("RoPPConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/RoPPConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/RoPPConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/RoPP
)

export(EXPORT RoPP-targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/RoPPTargets.cmake"
    NAMESPACE RoPP::
)
