# CMake list that build graphics engine dll

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
        CommandBuffer.cpp CommandBuffer.h SUniformBufferObject.h)

find_package(Vulkan REQUIRED)

message("${Core_LIBRARY}")

target_link_libraries(GraphicsEngine PUBLIC ${Vulkan_LIBRARIES})
target_link_libraries(GraphicsEngine PRIVATE ${Core})

target_include_directories(GraphicsEngine PUBLIC ${Vulkan_INCLUDE_DIR})
target_include_directories(GraphicsEngine PRIVATE ${Core_INCLUDE_DIR})