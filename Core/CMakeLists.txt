# CMakeList.txt : CMake project for Core, include source and define
# project specific logic here.
#
add_library(Core OBJECT
			Core.cpp Core.h
			Vector2F.h Vector2F.cpp
			Vector3F.h Vector3F.cpp
			Vector4F.h Vector4F.cpp)

#set(Core_LIBRARY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Core.lib" CACHE INTERNAL "")
set(Core_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Core/" CACHE INTERNAL "")

# TODO: Add tests and install targets if needed.
