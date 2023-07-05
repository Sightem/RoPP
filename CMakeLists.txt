cmake_minimum_required(VERSION 3.10)

project(RoPP VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

add_library(ropp ${SOURCE_FILES})

target_include_directories(ropp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${CMAKE_BUILD_TYPE}/RoPP>
)

find_package(CURL REQUIRED)

target_link_libraries(ropp PRIVATE CURL::libcurl)

include(GNUInstallDirs)

install(TARGETS ropp
    EXPORT RoPP-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CMAKE_BUILD_TYPE}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CMAKE_BUILD_TYPE}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${CMAKE_BUILD_TYPE}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_BUILD_TYPE}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_BUILD_TYPE}/RoPP)

install(EXPORT RoPP-targets
    FILE RoPPTargets.cmake
    NAMESPACE RoPP::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/RoPP/${CMAKE_BUILD_TYPE}
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
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/RoPP/${CMAKE_BUILD_TYPE}
)

export(EXPORT RoPP-targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/RoPPTargets.cmake"
    NAMESPACE RoPP::
)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
