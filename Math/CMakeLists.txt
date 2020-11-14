add_library(Math OBJECT
        Vector2F.h Vector2F.cpp
        Vector3F.h Vector3F.cpp
        Vector4F.h Vector4F.cpp
        Matrix.h
        Matrix4F.cpp Matrix4F.h
        Math_utils.inl Math_utils.h
        SRotation.h SRotation.cpp MathEngine.h)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Math/ .)
set(Math_INCLUDE_DIR "${INCLUDE_DIR}" CACHE INTERNAL "")

target_link_libraries(Math PUBLIC Debug)

target_include_directories(Math PUBLIC ${Math_INCLUDE_DIR})
target_include_directories(Math PUBLIC $<TARGET_PROPERTY:Debug,INCLUDE_DIRECTORIES>)

set_target_properties(Math PROPERTIES
        IMPORTED_LOCATION "${DEPENDENCIES_DIR}/math/bin/Math.dll"
        IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/math/lib/Math.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/math/include"
        )
