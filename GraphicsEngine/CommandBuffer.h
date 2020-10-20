//
// Created by tangt on 19/10/2020.
//
// Command buffer is use for bind a vertex and index buffer to the graphic pipeline and then use for render
//

#ifndef GAMEENGINE_COMMANDBUFFER_H
#define GAMEENGINE_COMMANDBUFFER_H

#include "vulkan/vulkan.hpp"

namespace graphics {

    class CommandPool;
    class Swapchain;
    class LogicalDevice;
    class Pipeline;

    class CommandBuffer {
    public:
        CommandBuffer() = default;

        void initialize(const Swapchain & swapchain);
        void release(const LogicalDevice & logicalDevice);
        void render(const Swapchain & swapchain,
                    const CommandPool & commandPool,
                    const Pipeline & pipeline,
                    const std::vector<uint32_t> & indices);

    private:
        std::vector<vk::CommandBuffer> m_commandBuffers;
    };

}
#endif //GAMEENGINE_COMMANDBUFFER_H
