cmake_minimum_required(VERSION 3.27)
project(JavalessMC)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/**)
file(GLOB_RECURSE ASN1C_SOURCES ${CMAKE_SOURCE_DIR}/cryptography/*.c)
include_directories(${CMAKE_SOURCE_DIR}/cryptography)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(JavalessMC ${SOURCES} ${ASN1C_SOURCES})

if(WIN32)
    target_link_libraries(JavalessMC ws2_32)
endif()