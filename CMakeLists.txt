cmake_minimum_required(VERSION 3.27)
project(JavalessMC)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/**)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(JavalessMC ${SOURCES})

if(WIN32)
    target_link_libraries(JavalessMC ws2_32)
endif()