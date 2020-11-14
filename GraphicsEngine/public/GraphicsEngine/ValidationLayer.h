//
// Created by tangt on 07/10/2020.
//
// Class that create validation layer, use for log debug informations from vulkan error
//

#ifndef GAMEENGINE_VALIDATIONLAYER_H
#define GAMEENGINE_VALIDATIONLAYER_H

#include "vulkan/vulkan.hpp"
#include <iostream>
#include <vector>
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace graphics {
    class Instance;

    class GRAPHICS_ENGINE_EXPORT ValidationLayer {
    public:
        ValidationLayer(); ///< Constructor will populate the debugMessenger info

        void initialize(const Instance & instance); ///< initialize validation layer from a given instance
        void release(const Instance & instance); ///< realease validation layer from a given instance

        const vk::DebugUtilsMessengerCreateInfoEXT & getDebugUtilsMessengerInfo() const; ///< Return debugMessenger information
        const std::vector<const char *> & getValidationLayerNames() const; ///< Return names of validation layer extension needed by vulkan
    protected:
    private:
        void populateDebugInfo(); ///< Populate m_debugUtilsMessengerInfo

        /**
         *
         * Function use to create the debug messenger
         * @param instance      Vulkan instance that use the messenger
         * @param pCreateInfo   Information of the messenger (m_debugUtilsMessengerInfo)
         * @param pAllocator    Callback allocator, generaly set at nullptr
         * @param pCallback     Callback when an message is throw by Vulkan
         * @return  Result of the operation
         */
        vk::Result createDebugMessanger(const VkInstance & instance, const
                                    VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const
                                    VkAllocationCallbacks* pAllocator,
                                    VkDebugUtilsMessengerEXT*pCallback);

        /**
         * Function that release debug messenger
         * @param instance      Vulkan instance
         * @param callback      Callback when an message is throw by Vulkan
         * @param pAllocator    Allocator callback, generaly set at nullptr
         */
        void releaseDebugMessanger(const VkInstance & instance,
                                   const VkDebugUtilsMessengerEXT & callback,
                                   const VkAllocationCallbacks* pAllocator);

        /**
         * Debug callback call when a Vulkan throw a message
         * @param messageSeverity   Severity of the message (warning, error, verbose)
         * @param messageTypes      Type of the message (general, performance, validation)
         * @param pCallbackData     Data of the message
         * @param pUserData         Data given by the user
         * @return  If the application must stop or not
         */
        static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageTypes,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData);

    public:
    protected:
    private:
        vk::DebugUtilsMessengerCreateInfoEXT m_debugUtilsMessengerInfo; ///< Informations of the messenger
        VkDebugUtilsMessengerEXT m_callback; ///< Callback instance

        std::vector<const char *> m_validationLayerNames; ///< Names of the extensions needed by Vulkan for instancing validation layer
    };

}

#endif //GAMEENGINE_VALIDATIONLAYER_H
