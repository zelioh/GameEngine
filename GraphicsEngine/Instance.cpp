//
// Created by tangt on 06/10/2020.
//

#include "Instance.h"
#include "InstanceParameter.h"
#include "ValidationLayer.h"

graphics::Instance * graphics::Instance::getInstance()
{
    static Instance * instance = nullptr;

    if (nullptr == instance)
    {
        instance = new Instance();
    }
    return instance;
}

graphics::Instance::Instance():
m_instance(),
m_appInfo(),
m_validationLayer(),
m_surface(),
m_vExtensions(),
m_isInitialize(false),
#if ENGINE_DEBUG ///< Set by cmake when build in debug mode
    m_bIsDebug(true)
#else
    m_bIsDebug(false)
#endif // ENGINE_DEBUG
{
}

void graphics::Instance::initialize(const InstanceParameter & parameters,const Window & window)
{
    m_appInfo.setPApplicationName(parameters.getApplicationName().c_str());
    m_appInfo.setApplicationVersion(VK_MAKE_VERSION(parameters.getProjectMajorVersion(),
                                                    parameters.getProjectMinorVersion(),
                                                    parameters.getProjectPatchVersion()
                                    ));
    m_appInfo.setPEngineName(ENGINE_NAME); ///< Set with cmake
    m_appInfo.setEngineVersion(
            VK_MAKE_VERSION(
                    ENGINE_VERSION_MAJOR, ///< Set with cmake
                    ENGINE_VERSION_MINOR, ///< Set with cmake
                    ENGINE_VERSION_PATCH ///< Set with cmake
            ));
    m_appInfo.setApiVersion(VK_API_VERSION_1_2);
    initializeInternal();
    m_validationLayer.initialize(*this);
    m_surface.initialize(*this, window);
    m_isInitialize = true;
}

void graphics::Instance::release()
{
    m_surface.release(*this);
    m_validationLayer.release(*this);
    m_instance.destroy(nullptr); ///< Realease instance
    m_isInitialize = false;
}

const vk::Instance & graphics::Instance::getVkInstance() const
{
    return m_instance;
}

const graphics::Surface & graphics::Instance::getSurface() const
{
    return m_surface;
}

const graphics::ValidationLayer & graphics::Instance::getValidationLayer() const
{
    return m_validationLayer;
}

void graphics::Instance::initializeInternal()
{
    vk::InstanceCreateInfo createInfo;

    createInfo.setPApplicationInfo(&m_appInfo);

    //
    // Set extention required by the engine
    fillRequiredExtension();
    createInfo.setEnabledExtensionCount(static_cast<uint32_t>(m_vExtensions.size()));
    createInfo.setPpEnabledExtensionNames(m_vExtensions.data());

    //
    // Set debug information logger
    if (m_bIsDebug)
    {
        const std::vector<const char *> & validationLayerNames = m_validationLayer.getValidationLayerNames();

        createInfo.setEnabledLayerCount(static_cast<uint32_t>(validationLayerNames.size()));
        createInfo.setPpEnabledLayerNames(validationLayerNames.data());
        createInfo.setPNext(&m_validationLayer.getDebugUtilsMessengerInfo());
    } else {
        createInfo.setEnabledLayerCount(0);
        createInfo.setPpEnabledLayerNames(nullptr);
        createInfo.setPNext(nullptr);
    }

    //
    // Create instance
    if (vk::createInstance(&createInfo, nullptr, &m_instance) != vk::Result::eSuccess)
    {
        throw std::runtime_error("Error while creating the Vulkan instance");
    }
}

void graphics::Instance::fillRequiredExtension()
{
    m_vExtensions.push_back("VK_KHR_surface");
    m_vExtensions.push_back("VK_KHR_win32_surface");
    if (m_bIsDebug)
    {
        m_vExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
}

graphics::Instance::operator bool() const
{
    return m_isInitialize;
}