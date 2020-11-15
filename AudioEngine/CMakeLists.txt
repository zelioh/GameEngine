cmake_minimum_required(VERSION 3.14)

project(AudioEngine)

add_library(audioEngine OBJECT
        AudioEngine.cpp AudioEngine.h)

target_link_libraries(audioEngine Winmm)
target_link_libraries(audioEngine Debug)

target_include_directories(audioEngine PUBLIC ${Debug_INCLUDE_DIR})

set(audioEngine_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/AudioEngine/ CACHE INTERNAL "")