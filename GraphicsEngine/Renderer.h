//
// Created by tangt on 26/10/2020.
//

#ifndef GAMEENGINE_RENDERER_H
#define GAMEENGINE_RENDERER_H

#include "Objects/GameObject.h"
#include "CommandBuffer.h"

namespace graphics {

    class Swapchain;

    class Renderer
    {
    public:
        Renderer(const Swapchain & swapchain);
        //
        // Depreased
        //bool renderObject(Swapchain & swapchain, const object::GameObject * object, const Pipeline & pipeline);

        //
        // Render the current Scene
        bool render(Swapchain & swapchain, const Pipeline & pipeline);
    private:
        bool renderBegin(Swapchain & swapchain);
        void renderElement(Swapchain & swapchain, const object::GameObject * object, const Pipeline & pipeline);
        bool renderEnd(Swapchain & swapchain, const Pipeline & pipeline);

        void update(const graphics::Swapchain & swapchain, int imageIndex, const object::GameObject * object);

        size_t m_currentFrame;
        uint32_t m_imageIndex;
        CommandBuffer m_commandBuffer;
    };

}

#endif //GAMEENGINE_RENDERER_H
