cmake_minimum_required(VERSION 3.0.0)
project(ropp VERSION 0.1.0 DESCRIPTION "Roblox API end-point wrapper ")

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

add_library(ropp STATIC)

file(GLOB source_files RoPP/*.cpp)
file(GLOB includ_source include/*.hpp)
target_sources(ropp
    PRIVATE
        ${source_files}
        ${includ_source}
)

target_include_directories(ropp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/RoPP
)

target_link_libraries(ropp
    PRIVATE
        curl
)

set(public_headers RoPP/ropp.h)

set_target_properties(ropp PROPERTIES
    PUBLIC_HEADER "${public_headers}"
)
