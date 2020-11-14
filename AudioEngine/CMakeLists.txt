cmake_minimum_required(VERSION 3.14)

project(AudioEngine)

add_library(audioEngine OBJECT
        AudioEngine.cpp AudioEngine.h)

target_link_libraries(audioEngine Winmm)