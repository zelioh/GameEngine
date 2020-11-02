# CMakeList.txt : CMake project for Core, include source and define
# project specific logic here.
#

add_library(PhysicsEngine OBJECT
			BoundingBox.h BoundingBox.cpp
			BoundingSphere.h BoundingSphere.cpp
			Plane.h Plane.cpp
			Collider.h Collider.cpp
			IntersectData.h IntersectData.cpp
			PhysicsObject.h PhysicsObject.cpp
			PhysicsEngine.h PhysicsEngine.cpp
			)

find_package(Vulkan REQUIRED)

target_link_libraries(PhysicsEngine PUBLIC ${Vulkan_LIBRARIES})
target_link_libraries(PhysicsEngine PRIVATE ${GraphicsEngine})

set(PhysicsEngine_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/PhysicsEngine/" CACHE INTERNAL "")

target_include_directories(PhysicsEngine PUBLIC ${Core_INCLUDE_DIR} ${Core_INCLUDE_DIR}/Objects/)
target_include_directories(PhysicsEngine PUBLIC ${GraphicsEngine_INCLUDE_DIR})

set_target_properties(PhysicsEngine PROPERTIES
		IMPORTED_LOCATION "${DEPENDENCIES_DIR}/PhysicsEngine/bin/PhysicsEngine.dll"
		IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/PhysicsEngine/lib/PhysicsEngine.lib"
		INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/PhysicsEngine/include"
		)

# TODO: Add tests and install targets if needed.
