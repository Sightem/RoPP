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

# Fetch and make CPR library available
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 3020c34ae2b732121f37433e61599c34535e68a8) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

# Make CPR include directories available to projects using RoPP
target_include_directories(ropp PUBLIC ${cpr_INCLUDE_DIRS})

target_link_libraries(ropp PRIVATE cpr)