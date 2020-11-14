//
// Created by tangt on 12/10/2020.
//
// Class use for get swapchain information with a given physicalDevice
//

#ifndef GAMEENGINE_SWAPCHAINDETAILS_H
#define GAMEENGINE_SWAPCHAINDETAILS_H

#include "vulkan/vulkan.hpp"
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace graphics {

    class PhysicalDevice;

    class GRAPHICS_ENGINE_EXPORT SwapchainDetails
    {
    public:
        SwapchainDetails(const PhysicalDevice &physicalDevice);

        const vk::SurfaceCapabilitiesKHR & getSurfaceCapabilities() const;
        const std::vector<vk::SurfaceFormatKHR> & getSurfaceFormats() const;
        const std::vector<vk::PresentModeKHR> & getPrensentModes() const;

    private:
        vk::SurfaceCapabilitiesKHR m_capabilities;
        std::vector<vk::SurfaceFormatKHR> m_formats;
        std::vector<vk::PresentModeKHR> m_presentModes;
    };
}


#endif //GAMEENGINE_SWAPCHAINDETAILS_H
