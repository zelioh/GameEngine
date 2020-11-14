cmake_minimum_required(VERSION 3.14)

project(AudioEngine)

add_library(audioEngine OBJECT
        AudioEngine.cpp AudioEngine.h)

target_link_libraries(audioEngine Winmm)

set(audioEngine_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/AudioEngine/ CACHE INTERNAL "")