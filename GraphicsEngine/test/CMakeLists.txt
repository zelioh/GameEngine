add_executable(GraphicsEngine_test WIN32 main.cpp)

target_link_libraries(GraphicsEngine_test PUBLIC Core)
target_link_libraries(GraphicsEngine_test PUBLIC Math)
target_link_libraries(GraphicsEngine_test PUBLIC Debug)
target_link_libraries(GraphicsEngine_test PUBLIC GraphicsEngine)
target_link_libraries(GraphicsEngine_test PUBLIC PhysicsEngine)
target_link_libraries(GraphicsEngine_test PUBLIC HIDEngine)

target_include_directories(GraphicsEngine_test PUBLIC ${Core_INCLUDE_DIR})
target_include_directories(GraphicsEngine_test PUBLIC ${GraphicsEngine_INCLUDE_DIR})
target_include_directories(GraphicsEngine_test PUBLIC ${PhysicalEngine_INCLUDE_DIR})
target_include_directories(GraphicsEngine_test PUBLIC ${HIDEngine_INCLUDE_DIR})
target_include_directories(GraphicsEngine_test PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/stb)


add_definitions(-DUNICODE)
