//
// Created by tangt on 12/10/2020.
//
// Class that represent the different queue usage in the engine
//

#ifndef GAMEENGINE_QUEUE_H
#define GAMEENGINE_QUEUE_H

#include "vulkan/vulkan.hpp"
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace graphics {

    class GRAPHICS_ENGINE_EXPORT Queue {
    public:
        Queue() = default;
        Queue(const vk::Queue & queue);

        const vk::Queue & getVkQueue() const;
    private:
        vk::Queue m_queue;
    };

}

#endif //GAMEENGINE_QUEUE_H
