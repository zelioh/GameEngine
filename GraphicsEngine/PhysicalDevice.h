//
// Created by tangt on 12/10/2020.
//
// Class that implement physical device creation in Vulkan. That represent all graphic card information of the computer
//

#ifndef GAMEENGINE_PHYSICALDEVICE_H
#define GAMEENGINE_PHYSICALDEVICE_H

#include "vulkan/vulkan.hpp"

namespace graphics {

    class Instance;

    class PhysicalDevice
    {
    public:
        static PhysicalDevice * getInstance();

        const vk::PhysicalDevice & getVkPhysicalDevice() const;
        const std::vector<const char *> & getDeviceExtensions() const;
        vk::Format findVkSupportedFormat(const std::vector<vk::Format> & candidates,
                                         vk::ImageTiling tiling,
                                         vk::FormatFeatureFlags features) const;
        uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags flags) const;
        vk::SampleCountFlagBits getVkMSSASample() const;

    private:
        PhysicalDevice();

        bool checkDeviceUsable();
        bool checkDeviceExtensionsSupport();
        vk::SampleCountFlagBits getMaxUsageSampleCount();

    private:
        vk::PhysicalDevice m_physicalDevice;
        const std::vector<const char *> m_vDeviceExtensions;
        vk::SampleCountFlagBits m_mssaSamples;
    };
}

#endif //GAMEENGINE_PHYSICALDEVICE_H
