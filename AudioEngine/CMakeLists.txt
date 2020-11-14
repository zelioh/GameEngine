cmake_minimum_required(VERSION 3.14)

project(AudioEngine)

add_library(AudioEngine SHARED
        AudioEngine.cpp AudioEngine.h)

add_executable(AudioEngineExe
        AudioEngine.cpp AudioEngine.h main.c)

target_link_libraries(AudioEngine Winmm)