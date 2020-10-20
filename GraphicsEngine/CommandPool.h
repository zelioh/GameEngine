//
// Created by tangt on 14/10/2020.
//
// Command pool is use to create command buffer
//

#ifndef GAMEENGINE_COMMANDPOOL_H
#define GAMEENGINE_COMMANDPOOL_H

#include "vulkan/vulkan.hpp"

namespace graphics {

    class LogicalDevice;

    class CommandPool
    {
    public:
        CommandPool() = default;

        void initialize(const LogicalDevice & logicalDevice);
        void release(const LogicalDevice & logicalDevice);
        const vk::CommandPool & getVkCommandPool() const;

    private:
        vk::CommandPool m_commandPool;
    };

}

#endif //GAMEENGINE_COMMANDPOOL_H
