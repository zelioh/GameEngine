//
// Created by tangt on 19/10/2020.
//
// Command buffer is use for bind a vertex and index buffer to the graphic pipeline and then use for render
//

#ifndef GAMEENGINE_COMMANDBUFFER_H
#define GAMEENGINE_COMMANDBUFFER_H

#include "vulkan/vulkan.hpp"
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace object
{
    class GameObject;
}

namespace Math
{
    class Matrix4F;
}

namespace graphics {

    class CommandPool;
    class Swapchain;
    class LogicalDevice;
    class Pipeline;

    class GRAPHICS_ENGINE_EXPORT CommandBuffer {
    public:
        CommandBuffer() = default;

        void initialize();
        void release();
        void beginRender(const Swapchain & swapchain, uint32_t imageIndex);
        void render(const Swapchain & swapchain,
                    const CommandPool & commandPool,
                    const Pipeline & pipeline,
                    const object::GameObject * object,
                    uint32_t imageIndex,
                    const Math::Matrix4F & projectionMatrix,
                    const Math::Matrix4F & viewMatrix);
        void endRender(uint32_t imageIndex, const Swapchain & swapchain);
        const vk::CommandBuffer & getCommandBuffer(uint32_t imageIndex) const;

    private:
        std::vector<vk::CommandBuffer> m_commandBuffers;
    };

}
#endif //GAMEENGINE_COMMANDBUFFER_H
