cmake_minimum_required(VERSION 3.27)
project(JavalessMC)

set(CMAKE_CXX_STANDARD 23)
set(LIBS ${CMAKE_SOURCE_DIR}/libs)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/**)
file(GLOB_RECURSE ASN1C_SOURCES ${CMAKE_SOURCE_DIR}/cryptography/*.c)
file(GLOB_RECURSE CRYPTOPP ${LIBS}/cryptopp/*.cpp)
include_directories(${CMAKE_SOURCE_DIR}/cryptography)
include_directories(${LIBS}/cryptopp)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(JavalessMC ${SOURCES} ${ASN1C_SOURCES} ${CRYPTOPP})

if(WIN32)
    target_link_libraries(JavalessMC ws2_32)
endif()