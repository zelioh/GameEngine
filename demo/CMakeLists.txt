project("DEMO")

cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

add_executable(demo main.cpp)
target_link_libraries(demo gameEngine Core Math GraphicsEngine)

target_include_directories(demo PUBLIC ${GAME_ENGINE_INCLUDE_DIRS})