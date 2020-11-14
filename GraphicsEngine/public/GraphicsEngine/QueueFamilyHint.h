//
// Created by tangt on 12/10/2020.
//
// Class use for check if a physical device can be use by Vulkan
//

#ifndef GAMEENGINE_QUEUEFAMILYHINT_H
#define GAMEENGINE_QUEUEFAMILYHINT_H

#include "vulkan/vulkan.hpp"
#include <optional>
#include "GraphicsEngine/GraphicsEngine.h"

namespace graphics
{
    class Surface;
    class PhysicalDevice;

    class GRAPHICS_ENGINE_EXPORT QueueFamilyHint
    {
    public:
        /**
         * Constructor that directly check is a physicalDevice have a graphicsFamily and a surface have a presentFamily
         * @param physicalDevice    device tested
         * @param surface           device tested
         */
        QueueFamilyHint(const PhysicalDevice & physicalDevice);

        bool isComplete() const; ///< Check if the queue family hint have a graphics and a present family

        uint32_t getGraphicsFamilyValue() const; ///< Gets the graphics family index in the physical device
        uint32_t getPresentFamilyValue() const; ///< Gets the presente family index in the surface

        explicit operator bool() const; ///< Returns isComplete
    private:
        std::optional<uint32_t> m_graphicsFamily;
        std::optional<uint32_t> m_presentFamily;
    };
}

#endif //GAMEENGINE_QUEUEFAMILYHINT_H
