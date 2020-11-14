//
// Created by tangt on 12/10/2020.
//
// Class use for get swapchain information with a given physicalDevice
//

#include "GraphicsEngine/SwapchainDetails.h"
#include "GraphicsEngine/PhysicalDevice.h"
#include "GraphicsEngine/Instance.h"

graphics::SwapchainDetails::SwapchainDetails(const graphics::PhysicalDevice &physicalDevice)
{
    graphics::Instance * instance = graphics::Instance::getInstance();

    const vk::SurfaceKHR & surface = instance->getSurface().getVulkanSurface();
    const vk::PhysicalDevice & vkDevice = physicalDevice.getVkPhysicalDevice();

    m_capabilities = vkDevice.getSurfaceCapabilitiesKHR(surface);
    m_formats = vkDevice.getSurfaceFormatsKHR(surface);
    m_presentModes = vkDevice.getSurfacePresentModesKHR(surface);
}

const vk::SurfaceCapabilitiesKHR & graphics::SwapchainDetails::getSurfaceCapabilities() const
{
    return m_capabilities;
}

const std::vector<vk::SurfaceFormatKHR> & graphics::SwapchainDetails::getSurfaceFormats() const
{
    return m_formats;
}

const std::vector<vk::PresentModeKHR> & graphics::SwapchainDetails::getPrensentModes() const
{
    return m_presentModes;
}