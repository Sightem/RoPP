cmake_minimum_required(VERSION 3.10)

project(RoPP VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
include_directories(include)

file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

add_library(ropp ${SOURCE_FILES})
add_library(RoPP::ropp ALIAS ropp)

target_include_directories(ropp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${CMAKE_BUILD_TYPE}/RoPP>
)

# Check if the cpr target is already defined
if (NOT TARGET cpr)
    # Fetch and make CPR library available
    FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                            GIT_TAG 3020c34ae2b732121f37433e61599c34535e68a8) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
    FetchContent_GetProperties(cpr)
    if (NOT cpr_POPULATED)
        FetchContent_Populate(cpr)
        add_subdirectory(${cpr_SOURCE_DIR} ${cpr_BINARY_DIR})
        set(cpr_install_target cpr) # This is added to handle the installation of cpr when building RoPP standalone
    endif()
endif()

target_link_libraries(ropp PRIVATE cpr)

include(GNUInstallDirs)

if(NOT ROPP_SKIP_INSTALL)
    install(TARGETS ropp ${cpr_install_target}
        EXPORT RoPP-Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CMAKE_BUILD_TYPE}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CMAKE_BUILD_TYPE}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${CMAKE_BUILD_TYPE}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_BUILD_TYPE}
    )
endif()

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_BUILD_TYPE}/RoPP)

install(EXPORT RoPP-Targets
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

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()