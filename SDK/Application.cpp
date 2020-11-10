//
// Created by FiercePC on 10/11/2020.
//

#include "Application.h"
#include "public/Core/Application.h"

sdk::Application::Application():
m_pApplication(nullptr)
{
    m_pApplication = new core::Application();
}

void sdk::Application::setPreInitializeCallback(const PreInitializeCallback &function)
{
    m_pApplication->setPreInitializeCallback(function);
}

void sdk::Application::setPostInitializeCallback(const PostInitializeCallback &function)
{
    m_pApplication->setPostInitializeCallback(function);
}

void sdk::Application::setPreUpdateFunction(const UpdateCallback &function)
{
    m_pApplication->setPreUpdateFunction(function);
}

void sdk::Application::setPostUpdateFunction(const UpdateCallback &function)
{
    m_pApplication->setPostUpdateFunction(function);
}

void sdk::Application::setPreReleaseCallback(const ReleaseCallback &function)
{
    m_pApplication->setPreReleaseCallback(function);
}

void sdk::Application::setPostReleaseCallback(const ReleaseCallback &function)
{
    m_pApplication->setPostReleaseCallback(function);
}

void sdk::Application::run()
{
    m_pApplication->run();
}