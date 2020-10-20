//
// Created by tangt on 12/10/2020.
//
// Class use for check if a physical device can be use by Vulkan
//

#include "QueueFamilyHint.h"
#include "Surface.h"
#include "PhysicalDevice.h"
#include "Instance.h"

graphics::QueueFamilyHint::QueueFamilyHint(const PhysicalDevice &physicalDevice)
{
    const vk::PhysicalDevice & vkDevice = physicalDevice.getVkPhysicalDevice();
    const vk::SurfaceKHR & vkSurface = physicalDevice.getParentInstance().getSurface().getVulkanSurface();
    std::vector<vk::QueueFamilyProperties> properties = vkDevice.getQueueFamilyProperties();
    uint32_t i = 0;

    for (const vk::QueueFamilyProperties & property : properties)
    {
        if (property.queueFlags & vk::QueueFlagBits::eGraphics)
        {
            m_graphicsFamily = i;
        }
        if (vkDevice.getSurfaceSupportKHR(i, vkSurface))
        {
            m_presentFamily = i;
        }
        if (isComplete())
        {
            break;
        }
        ++i;
    }
}

bool graphics::QueueFamilyHint::isComplete() const
{
    return m_graphicsFamily.has_value() && m_presentFamily.has_value();
}

uint32_t graphics::QueueFamilyHint::getGraphicsFamilyValue() const
{
    return m_graphicsFamily.value();
}

uint32_t  graphics::QueueFamilyHint::getPresentFamilyValue() const
{
    return m_presentFamily.value();
}

graphics::QueueFamilyHint::operator bool() const
{
    return isComplete();
}