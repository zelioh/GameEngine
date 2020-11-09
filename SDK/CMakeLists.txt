# CMakeList.txt : CMake project for Core, include source and define
# project specific logic here.
#
add_library(SDK OBJECT
        Cube.cpp Cube.h
        )

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SDK/ .)
set(SDK_INCLUDE_DIR "${INCLUDE_DIR}" CACHE INTERNAL "")

target_include_directories(SDK PUBLIC ${SDK_INCLUDE_DIR})

set_target_properties(SDK PROPERTIES
        IMPORTED_LOCATION "${DEPENDENCIES_DIR}/sdk/bin/SDK.dll"
        IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/sdk/lib/SDK.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/sdk/include"
        )