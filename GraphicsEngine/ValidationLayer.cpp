//
// Created by tangt on 07/10/2020.
//
// Class that create validation layer, use for log debug informations from vulkan error
//

#include "GraphicsEngine/ValidationLayer.h"
#include "GraphicsEngine/Instance.h"

graphics::ValidationLayer::ValidationLayer():
m_debugUtilsMessengerInfo(),
m_callback(),
m_validationLayerNames({"VK_LAYER_KHRONOS_validation"})
{
    populateDebugInfo();
}

void graphics::ValidationLayer::initialize(const Instance & instance)
{
    vk::Result result = createDebugMessanger((VkInstance const &)instance.getVkInstance(),
                         reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(&m_debugUtilsMessengerInfo),
                         nullptr,
                         &m_callback);

    if (result != vk::Result::eSuccess)
    {
        throw std::runtime_error("Errro while initialize validation layers");
    }
}

void graphics::ValidationLayer::release(const Instance & instance)
{
    releaseDebugMessanger((VkInstance const &) instance.getVkInstance(), m_callback, nullptr);
}

const vk::DebugUtilsMessengerCreateInfoEXT & graphics::ValidationLayer::getDebugUtilsMessengerInfo() const
{
    return m_debugUtilsMessengerInfo;
}

const std::vector<const char *> & graphics::ValidationLayer::getValidationLayerNames() const
{
    return m_validationLayerNames;
}

void graphics::ValidationLayer::populateDebugInfo()
{
    //
    // Set catch message with warning and error severity. Verbose is use to display the message
    m_debugUtilsMessengerInfo.setMessageSeverity(vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                                                 vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                                                 vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
                                                );
    //
    // Set catch message about generale information, performance issue and error/crash issues
    m_debugUtilsMessengerInfo.setMessageType(vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                                             vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
                                             vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
                                            );

    m_debugUtilsMessengerInfo.setPfnUserCallback(debugCallback);
    m_debugUtilsMessengerInfo.setPUserData(nullptr);
    m_debugUtilsMessengerInfo.setPNext(nullptr);
}

vk::Result graphics::ValidationLayer::createDebugMessanger(const VkInstance & instance, const
                                                            VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const
                                                            VkAllocationCallbacks* pAllocator,
                                                            VkDebugUtilsMessengerEXT*pCallback)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return static_cast<vk::Result>(func(instance, pCreateInfo, pAllocator, pCallback));
    } else {
        return vk::Result::eErrorExtensionNotPresent;
    }
}

void graphics::ValidationLayer::releaseDebugMessanger(const VkInstance & instance,
                                                      const VkDebugUtilsMessengerEXT & callback,
                                                      const VkAllocationCallbacks* pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, callback, pAllocator);
    }
}

VkBool32 graphics::ValidationLayer::debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {
    std::string strPrompt = "";

    if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        strPrompt += "Error ";
    } else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        strPrompt += "Warning ";
    } else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
        strPrompt += "Verbose ";
    } else {
        strPrompt += "Unknow severity";
    }

    if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
        strPrompt += "general: ";
    } else if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
        strPrompt += "performat: ";
    } else if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
        strPrompt += "validation: ";
    } else {
        strPrompt += "unknow type: ";
    }

    std::cerr << strPrompt << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}