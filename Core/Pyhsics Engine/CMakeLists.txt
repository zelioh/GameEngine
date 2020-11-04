# CMakeList.txt : CMake project for Core, include source and define
# project specific logic here.
#

add_executable(PhysicsEngine main.cpp)

add_library(PhysicsEngine OBJECT
			BoundingBox.h BoundingBox.cpp
			BoundingSphere.h BoundingSphere.cpp
			Plane.h Plane.cpp
			Collider.h Collider.cpp
			IntersectData.h IntersectData.cpp
			PhysicsObject.h PhysicsObject.cpp
			PhysicsEngine.h PhysicsEngine.cpp
			../Vector3F.h ../Vector3F.cpp
			main.cpp
			)


# TODO: Add tests and install targets if needed.
