# CMake list that build graphics engine dll

set(OBJECT_SRC
        Objects/GameObject.cpp Objects/GameObject.h
        Objects/Cube.cpp Objects/Cube.h
        Objects/CubeManager.cpp Objects/CubeManager.h
        Objects/ITextureObject.cpp Objects/ITextureObject.h
        Objects/Scene.cpp Objects/Scene.h
        Objects/SceneManager.cpp Objects/SceneManager.h
        Objects/CameraManager.cpp Objects/CameraManager.h
        Objects/Camera.cpp Objects/Camera.h
		Objects/Plane.cpp Objects/Plane.h
		Objects/PlaneManager.cpp Objects/PlaneManager.h
		Objects/Objects_utils.cpp Objects/Objects_utils.h
		Objects/Model3D.cpp Objects/Model3D.h
		Objects/Model3DManager.cpp Objects/Model3DManager.h
        Objects/LightManager.h Objects/LightManager.cpp
        Objects/Light.h Objects/Light.cpp
        )

add_library(GraphicsEngine OBJECT
        Instance.cpp Instance.h
        InstanceParameter.cpp InstanceParameter.h
        ValidationLayer.cpp ValidationLayer.h
        PhysicalDevice.cpp PhysicalDevice.h
        QueueFamilyHint.cpp QueueFamilyHint.h
        Surface.cpp Surface.h
        SwapchainDetails.cpp SwapchainDetails.h
        LogicalDevice.cpp LogicalDevice.h
        Queue.cpp Queue.h
        Swapchain.cpp Swapchain.h
        RenderPass.cpp RenderPass.h
        Pipeline.cpp Pipeline.h
        Shader.cpp Shader.h
        Vertex.cpp Vertex.h
        CommandPool.cpp CommandPool.h
        CommandBuffer.cpp CommandBuffer.h
        SUniformBufferObject.h
        TextureManager.cpp TextureManager.h
        Texture.cpp Texture.h
        Window.cpp Window.h
        WindowParameters.cpp WindowParameters.h
        Renderer.cpp Renderer.h
        ${OBJECT_SRC}
        )

find_package(Vulkan REQUIRED)
find_library(ws2_32_LIBRARY_PATH ws2_32)

target_link_libraries(GraphicsEngine PUBLIC ${Vulkan_LIBRARIES})
#target_link_libraries(GraphicsEngine PUBLIC ${ws2_32_LIBRARY_PATH})
target_link_libraries(GraphicsEngine PUBLIC Core)
target_link_libraries(GraphicsEngine PUBLIC PhysicsEngine)

target_include_directories(GraphicsEngine PUBLIC ${Vulkan_INCLUDE_DIR})
target_include_directories(GraphicsEngine PUBLIC ${Core_INCLUDE_DIR})
target_include_directories(GraphicsEngine PUBLIC ${PhysicalEngine_INCLUDE_DIR})
target_include_directories(GraphicsEngine PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/stb)
target_include_directories(GraphicsEngine PUBLIC Objects/)
target_include_directories(GraphicsEngine PUBLIC .)

add_definitions(-DUNICODE)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/GraphicsEngine/ ${Vulkan_INCLUDE_DIR} Objects/)

set(GraphicsEngine_INCLUDE_DIR "${INCLUDE_DIR}" CACHE INTERNAL "")

set_target_properties(GraphicsEngine PROPERTIES
        IMPORTED_LOCATION "${DEPENDENCIES_DIR}/graphics/bin/GraphicsEngine.dll"
        IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/graphics/lib/GraphicsEngine.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/graphics/include"
        )


add_subdirectory(test)