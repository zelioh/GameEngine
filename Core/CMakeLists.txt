# CMakeList.txt : CMake project for Core, include source and define
# project specific logic here.
#

add_library(Core OBJECT
			Core.cpp Core.h
			Vector2F.h Vector2F.cpp
			Vector3F.h Vector3F.cpp
			Vector4F.h Vector4F.cpp
			Matrix.h
			Matrix4F.cpp Matrix4F.h
			Math_utils.inl Math_utils.h
			)

find_package(Vulkan REQUIRED)

target_link_libraries(Core PUBLIC ${Vulkan_LIBRARIES})
target_link_libraries(Core PRIVATE ${GraphicsEngine})

set(Core_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Core/" CACHE INTERNAL "")

target_include_directories(Core PUBLIC ${Core_INCLUDE_DIR} ${Core_INCLUDE_DIR}/Objects/)
message(${GraphicsEngine_INCLUDE_DIR})
target_include_directories(Core PUBLIC ${GraphicsEngine_INCLUDE_DIR})

set_target_properties(Core PROPERTIES
		IMPORTED_LOCATION "${DEPENDENCIES_DIR}/core/bin/Core.dll"
		IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/core/lib/Core.lib"
		INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/core/include"
		)

# TODO: Add tests and install targets if needed.
