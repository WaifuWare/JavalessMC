cmake_minimum_required(VERSION 3.27)
project(JavalessMC)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(IS_DEBUG "turn on to test the software" OFF)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/**)
file(GLOB_RECURSE ASN1C_SOURCES ${CMAKE_SOURCE_DIR}/cryptography/*.c)
include_directories(${CMAKE_SOURCE_DIR}/cryptography)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_subdirectory(thirdparty/spdlog)

add_executable(JavalessMC ${SOURCES} ${ASN1C_SOURCES})

if(IS_DEBUG)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC DEBUG_MODE=1)
else()
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC DEBUG_MODE=0)
endif()

target_link_libraries(JavalessMC spdlog)

if(WIN32)
    target_link_libraries(JavalessMC ws2_32)
endif()
