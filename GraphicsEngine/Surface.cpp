//
// Created by tangt on 12/10/2020.
//
// Class that represent the surface use on the window
//

#include "Surface.h"
#include "Instance.h"
#include "Window.h"

void graphics::Surface::initialize(const Instance &instance, const Window & window)
{
    vk::Win32SurfaceCreateInfoKHR surfaceInfo;

    surfaceInfo.hwnd = window.getHWindow();
    surfaceInfo.hinstance = window.getHInstance();

    m_surface = instance.getVkInstance().createWin32SurfaceKHR(surfaceInfo);
    /*
    if (m_surface == nullptr)
    {
        throw std::runtime_error("Error while creating window surface");
    }
    */
}

void graphics::Surface::release(const Instance &instance)
{
    instance.getVkInstance().destroySurfaceKHR(m_surface);
}

const vk::SurfaceKHR & graphics::Surface::getVulkanSurface() const
{
    return m_surface;
}