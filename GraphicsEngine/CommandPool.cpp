//
// Created by tangt on 14/10/2020.
//
// Command pool is use to create command buffer
//

#include "CommandPool.h"
#include "PhysicalDevice.h"
#include "LogicalDevice.h"
#include "QueueFamilyHint.h"

void graphics::CommandPool::initialize(const LogicalDevice &logicalDevice)
{
    QueueFamilyHint hints(logicalDevice.getParentPhysicalDevice());
    vk::CommandPoolCreateInfo commandPoolInfo{};

    commandPoolInfo.queueFamilyIndex = hints.getGraphicsFamilyValue();
    m_commandPool = logicalDevice.getVkLogicalDevice().createCommandPool(commandPoolInfo);
    if (!m_commandPool)
    {
        throw std::runtime_error("Error while creating command pool");
    }
}

void graphics::CommandPool::release(const LogicalDevice &logicalDevice)
{
    logicalDevice.getVkLogicalDevice().destroyCommandPool(m_commandPool);
}

const vk::CommandPool & graphics::CommandPool::getVkCommandPool() const
{
    return m_commandPool;
}