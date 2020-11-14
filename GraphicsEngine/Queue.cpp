//
// Created by tangt on 12/10/2020.
//
// Class that represent the different queue usage in the engine
//

#include "GraphicsEngine/Queue.h"

graphics::Queue::Queue(const vk::Queue &queue):
m_queue(queue)
{
}

const vk::Queue & graphics::Queue::getVkQueue() const
{
    return m_queue;
}