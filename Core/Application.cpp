//
// Created by FiercePC on 09/11/2020.
//

#include "public/Core/Application.h"
#include "InstanceParameter.h"
#include "WindowParameters.h"
#include "public/GraphicsEngine/Window.h"

#include "Instance.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"
#include "Swapchain.h"
#include "Shader.h"
#include "Pipeline.h"
#include "Renderer.h"
#include "Objects/SceneManager.h"
#include "public/GraphicsEngine/TextureManager.h"
#include "WindowEvent.h"

#include <chrono>

core::Application::Application():
m_preInitCallback(),
m_postInitCallback(),
m_preUploadCallback(),
m_postUploadCallback(),
m_preReleaseCallback(),
m_postReleaseCallback(),
m_isRunning(false),
m_fDeltaTime(0.f),
m_projectionMatrix(MATRIX4F_IDENTITY),
m_renderer(nullptr),
m_pipeline(nullptr)
{
}

void core::Application::run()
{
    intialize();
    auto previousFrame = std::chrono::high_resolution_clock::now();
    m_isRunning = true;

    graphics::Swapchain * swapchain = graphics::Swapchain::getInstance();
    HID::WindowEvent * event = HID::WindowEvent::getInstance();
    graphics::Window * window = graphics::Window::getInstance();

    event->registerWindowCallback([](HID::window::Event id, int width, int height)
    {
        graphics::Window * window = graphics::Window::getInstance();

        window->resize(width, height);
        window->setResizeStatus(true);
    });

    while (*window)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousFrame).count();

        m_fDeltaTime = deltaTime;
        // handle window event
        // code here
        ///////////////////////

        window->handleEvent();
        if (!*window) {
            break;
        }

        // handle physics with factor
        // code here
        ///////////////////////////
        update(deltaTime);

        //
        // Render the current Scene
        if (window->wasResized() || !m_renderer->render(*swapchain, *m_pipeline))
        {
            swapchain->recreate( *m_pipeline, *m_renderer);
            window->setResizeStatus(false);
            LOG_MESSAGE("Window was resized");
        }

        previousFrame = currentTime;
        // if windows closed call stop() that set m_isRunning to false
    }
    release();
}

void core::Application::setPreInitializeCallback(const PreInitializeCallback & function)
{
    m_preInitCallback = function;
}

void core::Application::setPostInitializeCallback(const PostInitializeCallback & function)
{
    m_postInitCallback = function;
}

void core::Application::setPreUpdateFunction(const UpdateCallback &function)
{
    m_preUploadCallback = function;
}

void core::Application::setPostUpdateFunction(const UpdateCallback &function)
{
    m_postUploadCallback = function;
}

void core::Application::setPreReleaseCallback(const ReleaseCallback &function)
{
    m_preReleaseCallback = function;
}

void core::Application::setPostReleaseCallback(const ReleaseCallback &function)
{
    m_postReleaseCallback = function;
}

void core::Application::intialize()
{
    graphics::InstanceParameter instanceParameters;
    graphics::WindowParameters windowParameter;
    graphics::Window * window = graphics::Window::getInstance();

    if (m_preInitCallback)
    {
        m_preInitCallback(instanceParameters, windowParameter);
    }
    window->initialize(nullptr, windowParameter);

    graphics::Instance * instance = graphics::Instance::getInstance();

    instance->initialize(instanceParameters);

    graphics::PhysicalDevice * physicalDevice = graphics::PhysicalDevice::getInstance();
    graphics::LogicalDevice * logicalDevice = graphics::LogicalDevice::getInstance();
    graphics::Swapchain * swapchain = graphics::Swapchain::getInstance();

    swapchain->initialize();

    graphics::Shader shader("../shaders/defaultVert.spv", "../shaders/defaultFrag.spv");

    m_pipeline = new graphics::Pipeline(shader);
    m_renderer = new graphics::Renderer();

    if (m_postInitCallback)
    {
        m_postInitCallback();
    }
}

void core::Application::update(float deltaTime)
{
    graphics::Window * window = graphics::Window::getInstance();

    if (m_preUploadCallback)
    {
        m_preUploadCallback(deltaTime, m_projectionMatrix);
    }
    object::SceneManager::getInstance()->getCurrentScene()->getPhysicsEngine().CollisionHandler();
    object::SceneManager::getInstance()->getCurrentScene()->getPhysicsEngine().Update(deltaTime);
    object::SceneManager::getInstance()->getCurrentScene()->update();

    if (m_postUploadCallback) {
        m_postUploadCallback(deltaTime, m_projectionMatrix);
    }
    m_renderer->setProjectionMatrix(m_projectionMatrix);
}

void core::Application::stop()
{
    m_isRunning = false;
}

void core::Application::release()
{
    if (m_preReleaseCallback) {
        m_preReleaseCallback();
    }

    graphics::LogicalDevice::getInstance()->getVkLogicalDevice().waitIdle();
    graphics::TextureManager::getInstance()->release();
    object::SceneManager::getInstance()->release();
    m_pipeline->release();
    graphics::Swapchain::getInstance()->release();
    graphics::LogicalDevice::getInstance()->release();
    graphics::Instance::getInstance()->release();

    if (m_postReleaseCallback) {
        m_postReleaseCallback();
    }
}