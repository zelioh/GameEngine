# CMakeList.txt : CMake project for Core, include source and define
# project specific logic here.
#

add_library(Core OBJECT
			Core.cpp Core.h
        	Application.cpp public/Core/Application.h)


target_link_libraries(Core PRIVATE GraphicsEngine)
target_link_libraries(Core PUBLIC HIDEngine)
target_link_libraries(Core PUBLIC PhysicsEngine)
target_link_libraries(Core PUBLIC Math)
target_link_libraries(Core PUBLIC Debug)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Core/ . public/Core/)
set(Core_INCLUDE_DIR "${INCLUDE_DIR}" CACHE INTERNAL "")

target_include_directories(Core PUBLIC ${Core_INCLUDE_DIR})
target_include_directories(Core PRIVATE ${GraphicsEngine_INCLUDE_DIR})
target_include_directories(Core PUBLIC ${HIDEngine_INCLUDE_DIR})
target_include_directories(Core PUBLIC ${PhysicalEngine_INCLUDE_DIR})
target_include_directories(Core PUBLIC ${Math_INCLUDE_DIR})
target_include_directories(Core PUBLIC ${Debug_INCLUDE_DIR})

set_target_properties(Core PROPERTIES
		IMPORTED_LOCATION "${DEPENDENCIES_DIR}/core/bin/Core.dll"
		IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/core/lib/Core.lib"
		INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/core/include"
		)
