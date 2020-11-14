# CMakeList.txt : CMake project for Core, include source and define
# project specific logic here.
#
add_library(HIDEngine OBJECT
        Event.cpp Event.h
        WindowEvent.cpp WindowEvent.h)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/HIDEngine/)
set(HIDEngine_INCLUDE_DIR "${INCLUDE_DIR}" CACHE INTERNAL "")

set_target_properties(HIDEngine PROPERTIES
        IMPORTED_LOCATION "${DEPENDENCIES_DIR}/hid/bin/HIDEngine.dll"
        IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/hid/lib/HIDEngine.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/hid/include"
        )