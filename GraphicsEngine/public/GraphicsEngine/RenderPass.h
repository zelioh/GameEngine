//
// Created by tangt on 12/10/2020.
//
// Class use for the render pass instancing
//

#ifndef GAMEENGINE_RENDERPASS_H
#define GAMEENGINE_RENDERPASS_H

#include "vulkan/vulkan.hpp"
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace graphics {

    class Swapchain;

    class GRAPHICS_ENGINE_EXPORT RenderPass {
    public:
        RenderPass() = default;

        void initialize();
        void release();
        const vk::RenderPass & getVkRenderPass() const;

    private:
        vk::RenderPass m_renderPass;
    };

}

#endif //GAMEENGINE_RENDERPASS_H
