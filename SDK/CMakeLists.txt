# CMakeList.txt : CMake project for Core, include source and define
# project specific logic here.
#
add_library(SDK OBJECT
        Cube.cpp public/SDK/Cube.h
        CubeManager.cpp public/SDK/CubeManager.h
        GameObject.cpp public/SDK/GameObject.h
        Texture.cpp public/SDK/Texture.h
        TextureManager.cpp public/SDK/TextureManager.h
        Model3D.cpp public/SDK/Model3D.h
        Model3DManager.cpp public/SDK/Model3DManager.h
        Plane.cpp public/SDK/Plane.h
        PlaneManager.cpp public/SDK/PlaneManager.h
        Light.cpp public/SDK/Light.h
        LightManager.cpp public/SDK/LightManager.h
        Camera.cpp public/SDK/Camera.h
        CameraManager.cpp public/SDK/CameraManager.h Scene.cpp public/SDK/Scene.h SceneManager.cpp public/SDK/SceneManager.h Application.cpp public/SDK/Application.h Window.cpp public/SDK/Window.h public/SDK/SDK.h)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SDK/public/)
set(SDK_INCLUDE_DIR "${INCLUDE_DIR}" CACHE INTERNAL "")

target_link_libraries(SDK PRIVATE Core)
target_link_libraries(SDK PUBLIC PhysicsEngine)
target_link_libraries(SDK PRIVATE GraphicsEngine)

target_include_directories(SDK PUBLIC ${SDK_INCLUDE_DIR})
target_include_directories(SDK PRIVATE ${Core_INCLUDE_DIR})
target_include_directories(SDK PRIVATE ${GraphicsEngine_INCLUDE_DIR})
target_include_directories(SDK PRIVATE ${Math_INCLUDE_DIR})
target_include_directories(SDK PUBLIC ${PhysicalEngine_INCLUDE_DIR})
target_include_directories(SDK PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/stb)


set_target_properties(SDK PROPERTIES
        IMPORTED_LOCATION "${DEPENDENCIES_DIR}/sdk/bin/SDK.dll"
        IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/sdk/lib/SDK.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/sdk/include"
        )