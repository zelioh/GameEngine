# CMakeList.txt : CMake project for Core, include source and define
# project specific logic here.
#

set(OBJECT_SRC
		Objects/GameObject.cpp Objects/GameObject.h
		Objects/Cube.cpp Objects/Cube.h
		Objects/CubeManager.cpp Objects/CubeManager.h)

add_library(Core OBJECT
			Core.cpp Core.h
			Vector2F.h Vector2F.cpp
			Vector3F.h Vector3F.cpp
			Vector4F.h Vector4F.cpp
			Matrix.h Matrix.cpp
			${OBJECT_SRC}
		)

find_package(Vulkan REQUIRED)

target_link_libraries(Core PUBLIC ${Vulkan_LIBRARIES})
target_link_libraries(Core PRIVATE ${GraphicsEngine})

target_include_directories(Core PUBLIC ${Core_INCLUDE_DIR} ${Core_INCLUDE_DIR}/Objects/)
target_include_directories(Core PUBLIC ${GraphicsEngine_INCLUDE_DIR})

set(Core_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Core/" CACHE INTERNAL "")

set_target_properties(Core PROPERTIES
		IMPORTED_LOCATION "${DEPENDENCIES_DIR}/core/bin/Core.dll"
		IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/core/lib/Core.lib"
		INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/core/include"
		)

# TODO: Add tests and install targets if needed.
