# CMakeList.txt : CMake project for Core, include source and define
# project specific logic here.
#

add_library(Debug OBJECT
        Debug_utils.h Debug_utils.inl)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Debug/ .)
set(Debug_INCLUDE_DIR "${INCLUDE_DIR}" CACHE INTERNAL "")

target_include_directories(Debug PUBLIC ${Debug_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/Debug/ .)

set_target_properties(Debug PROPERTIES
        IMPORTED_LOCATION "${DEPENDENCIES_DIR}/debug/bin/Debug.dll"
        IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/debug/lib/Debug.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/debug/include"
        )
