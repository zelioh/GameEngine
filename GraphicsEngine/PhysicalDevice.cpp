//
// Created by tangt on 12/10/2020.
//
// Class that implement physical device creation in Vulkan. That represent all graphic card information of the computer
//

#include "PhysicalDevice.h"
#include "QueueFamilyHint.h"
#include "SwapchainDetails.h"
#include "Instance.h"
#include <set>

graphics::PhysicalDevice * graphics::PhysicalDevice::getInstance()
{
    static graphics::PhysicalDevice * physicalDevice = nullptr;

    if (nullptr == physicalDevice)
    {
        physicalDevice = new PhysicalDevice();
    }
    return physicalDevice;
}

graphics::PhysicalDevice::PhysicalDevice():
m_vDeviceExtensions({VK_KHR_SWAPCHAIN_EXTENSION_NAME}),
m_mssaSamples(vk::SampleCountFlagBits::e1)
{
    graphics::Instance * instance = graphics::Instance::getInstance();

    if (!instance)
    {
        throw std::runtime_error("Instance must be initialize before creating physical device");
    }

    uint32_t iDeviceNumber = 0;

    std::vector<vk::PhysicalDevice> result  = instance->getVkInstance().enumeratePhysicalDevices();

    for (const vk::PhysicalDevice & device : result)
    {
        m_physicalDevice = device;
        if (!checkDeviceUsable())
        {
            m_physicalDevice = nullptr;
        } else {
            break;
        }
    }
    /*
    if (m_physicalDevice == nullptr)
    {
        throw std::runtime_error("Error while creating physical device");
    }
    */
    m_mssaSamples = getMaxUsageSampleCount();
}

const vk::PhysicalDevice & graphics::PhysicalDevice::getVkPhysicalDevice() const
{
    return m_physicalDevice;
}

const std::vector<const char *> & graphics::PhysicalDevice::getDeviceExtensions() const
{
    return m_vDeviceExtensions;
}

vk::Format graphics::PhysicalDevice::findVkSupportedFormat(const std::vector<vk::Format> &candidates,
                                                           vk::ImageTiling tiling,
                                                           vk::FormatFeatureFlags features) const
{
    for (vk::Format format : candidates)
    {
        vk::FormatProperties props{};

        m_physicalDevice.getFormatProperties(format, &props);
        if (vk::ImageTiling::eLinear == tiling && (props.linearTilingFeatures & features) == features)
        {
            return format;
        } else if (vk::ImageTiling::eOptimal == tiling && (props.optimalTilingFeatures & features) == features) {
            return format;
        }
    }
    throw std::runtime_error("Error no format supported by the physical device");
}

bool graphics::PhysicalDevice::checkDeviceUsable()
{
    QueueFamilyHint hints(*this);
    vk::PhysicalDeviceProperties properties = m_physicalDevice.getProperties();
    vk::PhysicalDeviceFeatures features = m_physicalDevice.getFeatures();
    bool extentionAvaible = checkDeviceExtensionsSupport();
    bool swapchainUsage = false;

    if (extentionAvaible)
    {
        graphics::SwapchainDetails details(*this);

        swapchainUsage = !details.getSurfaceFormats().empty() && !details.getPrensentModes().empty();
    }
    return properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu &&
            features.geometryShader && features.samplerAnisotropy &&
            hints && extentionAvaible && swapchainUsage;
}

bool graphics::PhysicalDevice::checkDeviceExtensionsSupport()
{
    std::vector<vk::ExtensionProperties> extensionsNames = m_physicalDevice.enumerateDeviceExtensionProperties();
    std::set<std::string> requiredExtension(m_vDeviceExtensions.begin(), m_vDeviceExtensions.end());

    for (const vk::ExtensionProperties & extensionName : extensionsNames)
    {
        requiredExtension.erase(extensionName.extensionName);
    }
    return requiredExtension.empty();
}

uint32_t graphics::PhysicalDevice::findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags flags) const
{
    vk::PhysicalDeviceMemoryProperties memoryProperties = m_physicalDevice.getMemoryProperties();
    const uint32_t count = memoryProperties.memoryTypeCount;

    for (uint32_t i = 0; i < count; ++i)
    {
        if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & flags) == flags)
        {
            return i;
        }
    }
    throw std::runtime_error("Error can't find memory type for a buffer");
}

vk::SampleCountFlagBits graphics::PhysicalDevice::getMaxUsageSampleCount()
{
    vk::PhysicalDeviceProperties props = m_physicalDevice.getProperties();
    vk::SampleCountFlags flags = props.limits.framebufferColorSampleCounts & props.limits.framebufferDepthSampleCounts;

    if ((flags & vk::SampleCountFlagBits::e64) == vk::SampleCountFlagBits::e64) return vk::SampleCountFlagBits::e64;
    if ((flags & vk::SampleCountFlagBits::e32) == vk::SampleCountFlagBits::e32) return vk::SampleCountFlagBits::e32;
    if ((flags & vk::SampleCountFlagBits::e16) == vk::SampleCountFlagBits::e16) return vk::SampleCountFlagBits::e16;
    if ((flags & vk::SampleCountFlagBits::e8) == vk::SampleCountFlagBits::e8) return vk::SampleCountFlagBits::e8;
    if ((flags & vk::SampleCountFlagBits::e4) == vk::SampleCountFlagBits::e4) return vk::SampleCountFlagBits::e4;
    if ((flags & vk::SampleCountFlagBits::e2) == vk::SampleCountFlagBits::e2) return vk::SampleCountFlagBits::e2;
    return vk::SampleCountFlagBits::e1;
}

vk::SampleCountFlagBits graphics::PhysicalDevice::getVkMSSASample() const {
    return m_mssaSamples;
}