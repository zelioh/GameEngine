//
// Created by tangt on 06/10/2020.
//
// This class represent the vulkan instance, it contain application informations
//

#ifndef GAMEENGINE_INSTANCE_H
#define GAMEENGINE_INSTANCE_H

#include "vulkan/vulkan.hpp"
#include "ValidationLayer.h"
#include "Surface.h"
#include <vector>

namespace graphics
{
    class InstanceParameter;

    class Instance {
    public:
            Instance(); ///< Constructor that implement m_instance;
            Instance(const InstanceParameter & parameters); ///< Constructor that implement m_instance with user parameters

            void initialize(); ///< Initialize vulkan instance
            void release(); ///< Destroy the vulkan instance

            const vk::Instance & getVkInstance() const; ///< Returns the Vulkan instance for use it
            const Surface & getSurface() const; ///< Returns vulkan surface use into the window

            const ValidationLayer & getValidationLayer() const; ///< Returns validation layer

    protected:
    private:
        void initializeInternal();
        void fillRequiredExtension();

    public:
    protected:
    private:
            vk::Instance m_instance;
            vk::ApplicationInfo m_appInfo;
            graphics::ValidationLayer m_validationLayer;
            graphics::Surface m_surface;

            std::vector<const char *> m_vExtensions;
            const bool m_bIsDebug;
    };
}

#endif //GAMEENGINE_INSTANCE_H
