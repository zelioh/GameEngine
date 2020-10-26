//
// Created by tangt on 12/10/2020.
//
// Class that represent the surface use on the window
//

#ifndef GAMEENGINE_SURFACE_H
#define GAMEENGINE_SURFACE_H

#define VK_USE_PLATFORM_WIN32_KHR
#include "vulkan/vulkan.hpp"

namespace graphics {
    class Instance;
    class Window;

    class Surface {
    public:
        Surface() = default;

        void initialize(const Instance & instance, const Window & window);  ///< TODO: use WIN32 window in constructor
        void release(const Instance & instance);

        const vk::SurfaceKHR & getVulkanSurface() const;

    private:
        vk::SurfaceKHR m_surface;
    };
}

#endif //GAMEENGINE_SURFACE_H
