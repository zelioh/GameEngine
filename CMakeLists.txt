cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0005 NEW)

project("GameEngine" VERSION 0.1.0)

add_definitions(-DENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
                -DENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
                -DENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
                -DENGINE_NAME="${PROJECT_NAME}"
        )

add_definitions(-DgameEngine_EXPORTS=1)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    message(FATAL_ERROR "You must use CMAKE_BUILD_TYPE with Debug or Master value. In command line use -DCMAKE_BUILD_TYPE=Debug")
endif (NOT DEFINED CMAKE_BUILD_TYPE)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_definitions(-DENGINE_DEBUG=1)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

add_subdirectory(Debug)
add_subdirectory(Math)
add_subdirectory(AudioEngine)
add_subdirectory(HIDEngine)
add_subdirectory(Core)
add_subdirectory(PhysicsEngine)
add_subdirectory(GraphicsEngine)
add_subdirectory(SDK)

include(GenerateExportHeader)

add_library(gameEngine SHARED null.cpp)

GENERATE_EXPORT_HEADER(gameEngine
        BASE_NAME gameEngine
        EXPORT_MACRO_NAME gameEngine_EXPORTS
        EXPORT_FILE_NAME gameEngine_exports.h
        STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)

target_link_libraries(gameEngine PRIVATE
                                audioEngine
                                PhysicsEngine
                                GraphicsEngine
                                )

target_link_libraries(gameEngine PUBLIC
                                Core
                                Debug
                                Math
                                HIDEngine
                                SDK)

target_compile_definitions(gameEngine PRIVATE DLL)

set(GAME_ENGINE_LIBRARIES Core audioEngine PhysicsEngine GraphicsEngine Debug Math HIDEngine SDK)
set(GAME_ENGINE_INCLUDE_DIRS ${Core_INCLUDE_DIR}
                             ${audioEngine_INCLUDE_DIR}
                             ${PhysicalEngine_INCLUDE_DIR}
                             ${GraphicsEngine_INCLUDE_DIR}
                             ${Debug_INCLUDE_DIR}
                             ${Math_INCLUDE_DIR}
                             ${HIDEngine_INCLUDE_DIR}
                             ${SDK_INCLUDE_DIR}
        )

set_target_properties(gameEngine PROPERTIES
                        IMPORTED_LOCATION "${GAME_ENGINE_LIBRARIES}"
                        INTERFACE_INCLUDE_DIRECTORIES "${GAME_ENGINE_INCLUDE_DIRS}")

add_subdirectory(demo)