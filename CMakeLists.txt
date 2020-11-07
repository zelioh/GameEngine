cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0005 NEW)

project("GameEngine" VERSION 0.1.0)

add_definitions(-DENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
                -DENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
                -DENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
                -DENGINE_NAME="${PROJECT_NAME}"
        )

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_definitions(-DENGINE_DEBUG=1)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

add_subdirectory(AudioEngine)
add_subdirectory(HIDEngine)
add_subdirectory(Core)
add_subdirectory(PhysicsEngine)
add_subdirectory(GraphicsEngine)

add_library(gameEngine SHARED null.cpp)
target_link_libraries(gameEngine PRIVATE
                                ${Core}
                                ${audio}
                                ${GraphicsEngine}
                                ${PhysicsEngine})

target_link_libraries(gameEngine PUBLIC
                                ${HIDEngine})