//
// Created by FiercePC on 09/11/2020.
//

#include "Application.h"
#include "InstanceParameter.h"
#include "WindowParameters.h"

core::Application::Application():
m_preInitCallback(),
m_postInitCallback(),
m_preUploadCallback(),
m_postUploadCallback(),
m_preReleaseCallback(),
m_postReleaseCallback()
{
}

void core::Application::run()
{
    intialize();
    while (1)
    {
        update(0.0f);
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

void core::Application::release()
{
    m_preReleaseCallback();

    // Release

    m_postReleaseCallback();
}