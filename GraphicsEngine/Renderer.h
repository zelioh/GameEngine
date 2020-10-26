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
        // Care here swapchain is not constant because we need to create the vertex and index buffer inside of it
        bool renderObject(Swapchain & swapchain, const object::GameObject * object, const Pipeline & pipeline);
    private:
        bool renderBegin(const Swapchain & swapchain);
        void render(Swapchain & swapchain, const object::GameObject * object, const Pipeline & pipeline);
        bool renderEnd(Swapchain & swapchain, const Pipeline & pipeline);

        size_t m_currentFrame;
        uint32_t m_imageIndex;
        CommandBuffer m_commandBuffer;
    };

}

#endif //GAMEENGINE_RENDERER_H
