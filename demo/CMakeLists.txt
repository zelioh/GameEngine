project("DEMO")

cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_FIND_LIBRARY_PREFIXES "")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")

find_library(engine_LIB gameEngine HINTS ${CMAKE_CURRENT_SOURCE_DIR} .. ../../build)

message("GAME_ENGINE_INCLUDE_DIRS==${GAME_ENGINE_INCLUDE_DIRS}")
message("GAME_ENGINE_LIBRARIES==${GAME_ENGINE_LIBRARIES}")
message("engine_LIB==${engine_LIB}")
message("gameEngine==${gameEngine}")
message("gameEngine_INCLUDE_DIRS==${gameEngine_INCLUDE_DIRS}")

add_executable(demo main.cpp)
target_link_libraries(demo ${engine_LIB})
target_include_directories(demo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../GraphicsEngine/
                                       ${CMAKE_CURRENT_SOURCE_DIR}/../GraphicsEngine/Object/)