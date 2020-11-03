//
// Created by tangt on 26/10/2020.
//

#ifndef GAMEENGINE_RENDERER_H
#define GAMEENGINE_RENDERER_H

#include "Objects/GameObject.h"
#include "CommandBuffer.h"

//namespace Math
//{
//    class Matrix4F;
//}

namespace graphics {

    class Swapchain;

    class Renderer
    {
    public:
        Renderer(const Swapchain & swapchain);

        //
        // Render the current Scene
        bool render(Swapchain & swapchain, const Pipeline & pipeline);

        /**
         * Set the projection matrix use for render.
         * You can use Math::utils::persepective to compute it, located in Math_utils.h
         * @param projection    Matrix of projection
         */
        void setProjectionMatrix(const Math::Matrix4F & projection);
    private:
        bool renderBegin(Swapchain & swapchain);
        void renderElement(Swapchain & swapchain,
                           const object::GameObject * object,
                           const Pipeline & pipeline,
                           const Math::Matrix4F & projectionMatrix);
        bool renderEnd(Swapchain & swapchain, const Pipeline & pipeline);

        void update(const graphics::Swapchain & swapchain, int imageIndex, const object::GameObject * object);

        size_t m_currentFrame;
        uint32_t m_imageIndex;
        CommandBuffer m_commandBuffer;

        Math::Matrix4F m_projection;
    };

}

#endif //GAMEENGINE_RENDERER_H
