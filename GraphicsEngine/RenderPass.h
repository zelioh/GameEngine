//
// Created by tangt on 12/10/2020.
//
// Class use for the render pass instancing
//

#ifndef GAMEENGINE_RENDERPASS_H
#define GAMEENGINE_RENDERPASS_H

#include "vulkan/vulkan.hpp"

namespace graphics {

    class Swapchain;

    class RenderPass {
    public:
        RenderPass() = default;

        void initialize(const Swapchain & swapchain);
        void release(const Swapchain & swapchain);
        const vk::RenderPass & getVkRenderPass() const;

    private:
        vk::RenderPass m_renderPass;
    };

}

#endif //GAMEENGINE_RENDERPASS_H