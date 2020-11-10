//
// Created by FiercePC on 09/11/2020.
//

#include "public/Core/Application.h"
#include "InstanceParameter.h"
#include "WindowParameters.h"

#include <chrono>

core::Application::Application():
m_preInitCallback(),
m_postInitCallback(),
m_preUploadCallback(),
m_postUploadCallback(),
m_preReleaseCallback(),
m_postReleaseCallback(),
m_isRunning(false),
m_fDeltaTime(0.f)
{
}

void core::Application::run()
{
    intialize();
    auto startTime = std::chrono::high_resolution_clock::now();
    auto previousFrame = std::chrono::high_resolution_clock::now();
    m_isRunning = true;
    while (m_isRunning)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
        float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(
            currentTime - previousFrame).count();

        m_fDeltaTime = deltaTime;
        // handle window event
            // code here
        ///////////////////////

        float moveFactor = 2.5f * m_fDeltaTime;

        // handle physics with factor
            // code here
        ///////////////////////////
        update(0.0f);

        // handle graphics code here ///

        previousFrame = currentTime;
        // if windows closed call stop() taht set m_isRunning to false
    }
    release();
}

void core::Application::setPreInitializeCallback(const PreInitializeCallback & function)
{
    m_preInitCallback = function;
}

void core::Application::setPostInitializeCallback(const PostInitializeCallback & function)
{
    m_postReleaseCallback = function;
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

    m_preInitCallback(instanceParameters, windowParameter);

    // initialize

    m_postInitCallback();
}

void core::Application::update(float deltaTime)
{
    m_preUploadCallback(deltaTime);

    //Upload

    m_postUploadCallback(deltaTime);
}

void core::Application::stop()
{
    m_isRunning = false;
}

void core::Application::release()
{
    m_preReleaseCallback();

    // Release


    m_postReleaseCallback();
}