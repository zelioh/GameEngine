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
        PhysicsEngine_public.h)

target_link_libraries(PhysicsEngine PUBLIC Math)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/PhysicsEngine/)
set(PhysicalEngine_INCLUDE_DIR "${INCLUDE_DIR}" CACHE INTERNAL "")

target_include_directories(PhysicsEngine PUBLIC ${Math_INCLUDE_DIR})
target_include_directories(PhysicsEngine PUBLIC ${PhysicalEngine_INCLUDE_DIR})
target_include_directories(PhysicsEngine PUBLIC .)

set_target_properties(PhysicsEngine PROPERTIES
		IMPORTED_LOCATION "${DEPENDENCIES_DIR}/physics/bin/PhysicsEngine.dll"
		IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/physics/lib/PhysicsEngine.lib"
		INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/physics/include"
		)

add_subdirectory(test)


# TODO: Add tests and install targets if needed.
