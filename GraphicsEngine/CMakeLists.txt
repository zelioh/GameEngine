# CMake list that build graphics engine dll

set(OBJECT_SRC
        Objects/GameObject.cpp public/GraphicsEngine/GameObject.h
        Objects/Cube.cpp public/GraphicsEngine/Cube.h
        Objects/CubeManager.cpp public/GraphicsEngine/CubeManager.h
        Objects/ITextureObject.cpp public/GraphicsEngine/ITextureObject.h
        Objects/Scene.cpp public/GraphicsEngine/Scene.h
        Objects/SceneManager.cpp public/GraphicsEngine/SceneManager.h
        Objects/CameraManager.cpp public/GraphicsEngine/CameraManager.h
        Objects/Camera.cpp public/GraphicsEngine/Camera.h
		Objects/Plane.cpp public/GraphicsEngine/Plane.h
		Objects/PlaneManager.cpp public/GraphicsEngine/PlaneManager.h
		Objects/Objects_utils.cpp public/GraphicsEngine/Objects_utils.h
		Objects/Model3D.cpp public/GraphicsEngine/Model3D.h
		Objects/Model3DManager.cpp public/GraphicsEngine/Model3DManager.h
		public/GraphicsEngine/LightManager.h Objects/LightManager.cpp
		public/GraphicsEngine/Light.h Objects/Light.cpp
        )

add_library(GraphicsEngine OBJECT
        Instance.cpp public/GraphicsEngine/Instance.h
        InstanceParameter.cpp public/GraphicsEngine/InstanceParameter.h
        ValidationLayer.cpp public/GraphicsEngine/ValidationLayer.h
        PhysicalDevice.cpp public/GraphicsEngine/PhysicalDevice.h
        QueueFamilyHint.cpp public/GraphicsEngine/QueueFamilyHint.h
        Surface.cpp public/GraphicsEngine/Surface.h
        SwapchainDetails.cpp public/GraphicsEngine/SwapchainDetails.h
        LogicalDevice.cpp public/GraphicsEngine/LogicalDevice.h
        Queue.cpp public/GraphicsEngine/Queue.h
        Swapchain.cpp public/GraphicsEngine/Swapchain.h
        RenderPass.cpp public/GraphicsEngine/RenderPass.h
        Pipeline.cpp public/GraphicsEngine/Pipeline.h
        Shader.cpp public/GraphicsEngine/Shader.h
        Vertex.cpp public/GraphicsEngine/Vertex.h
        CommandPool.cpp public/GraphicsEngine/CommandPool.h
        CommandBuffer.cpp public/GraphicsEngine/CommandBuffer.h
		public/GraphicsEngine/SUniformBufferObject.h
        TextureManager.cpp public/GraphicsEngine/TextureManager.h
        Texture.cpp public/GraphicsEngine/Texture.h
        Window.cpp public/GraphicsEngine/Window.h
        WindowParameters.cpp public/GraphicsEngine/WindowParameters.h
        Renderer.cpp public/GraphicsEngine/Renderer.h
        ${OBJECT_SRC}
		public/GraphicsEngine/GraphicsEngine.h)

find_package(Vulkan REQUIRED)

target_link_libraries(GraphicsEngine PUBLIC ${Vulkan_LIBRARIES})
target_link_libraries(GraphicsEngine PUBLIC Math)
target_link_libraries(GraphicsEngine PUBLIC Debug)
target_link_libraries(GraphicsEngine PUBLIC PhysicsEngine)
target_link_libraries(GraphicsEngine PUBLIC HIDEngine)

target_include_directories(GraphicsEngine PUBLIC ${CMAKE_SOURCE_DIR}/GraphicsEngine/Objects/)
target_include_directories(GraphicsEngine PUBLIC ${CMAKE_SOURCE_DIR}/GraphicsEngine/public/)
target_include_directories(GraphicsEngine PUBLIC ${Vulkan_INCLUDE_DIR})
target_include_directories(GraphicsEngine PUBLIC ${CMAKE_SOURCE_DIR}/GraphicsEngine)
target_include_directories(GraphicsEngine PUBLIC ${Debug_INCLUDE_DIR})
target_include_directories(GraphicsEngine PUBLIC ${PhysicalEngine_INCLUDE_DIR})
target_include_directories(GraphicsEngine PUBLIC ${HIDEngine_INCLUDE_DIR})
target_include_directories(GraphicsEngine PUBLIC ${Math_INCLUDE_DIR})
target_include_directories(GraphicsEngine PUBLIC $<TARGET_PROPERTY:Math,INCLUDE_DIRECTORIES>)
target_include_directories(GraphicsEngine PUBLIC ${CMAKE_SOURCE_DIR}/Math)
target_include_directories(GraphicsEngine PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/stb)

add_definitions(-DUNICODE)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/GraphicsEngine/ ${Vulkan_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/GraphicsEngine/Objects/ ${CMAKE_SOURCE_DIR}/GraphicsEngine/public/)

set(GraphicsEngine_INCLUDE_DIR "${INCLUDE_DIR}" CACHE INTERNAL "")

set_target_properties(GraphicsEngine PROPERTIES
        IMPORTED_LOCATION "${DEPENDENCIES_DIR}/graphics/bin/GraphicsEngine.dll"
        IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/graphics/lib/GraphicsEngine.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/graphics/include"
        )


add_subdirectory(test)