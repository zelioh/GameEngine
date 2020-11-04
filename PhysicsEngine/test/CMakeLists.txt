add_executable(PhysicalEngine_test main.cpp)

target_link_libraries(PhysicalEngine_test PUBLIC PhysicsEngine)
target_link_libraries(PhysicalEngine_test PUBLIC Core)

target_include_directories(PhysicalEngine_test PUBLIC ${PhysicalEngine_INCLUDE_DIR})
target_include_directories(PhysicalEngine_test PUBLIC ${Core_INCLUDE_DIR})

