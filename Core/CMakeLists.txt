# CMakeList.txt : CMake project for Core, include source and define
# project specific logic here.
#

set(OBJECT_SRC
		Objects/GameObject.cpp Objects/GameObject.h
		Objects/Cube.cpp Objects/Cube.h
		Objects/CubeManager.cpp Objects/CubeManager.h
		Objects/ITextureObject.cpp Objects/ITextureObject.h
		Objects/Scene.cpp Objects/Scene.h
		Objects/SceneManager.cpp Objects/SceneManager.h
		Objects/SRotation.cpp Objects/SRotation.h
		Objects/CameraManager.cpp Objects/CameraManager.h
		Objects/Camera.cpp Objects/Camera.h)

add_library(Core OBJECT
			Core.cpp Core.h
			Vector2F.h Vector2F.cpp
			Vector3F.h Vector3F.cpp
			Vector4F.h Vector4F.cpp
			Matrix.h
			Matrix4F.cpp Matrix4F.h
			Math_utils.inl Math_utils.h
			${OBJECT_SRC}
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
