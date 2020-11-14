//
// Created by FiercePC on 11/11/2020.
//

#include "public/SDK/Window.h"
#include "public/GraphicsEngine/Window.h"

sdk::Window::Window():
m_pWindow(graphics::Window::getInstance())
{
}

HWND sdk::Window::getHWindow() const
{
    return m_pWindow->getHWindow();
}

int sdk::Window::getWidth() const
{
    return m_pWindow->getWidth();
}

int sdk::Window::getHeight() const
{
    return m_pWindow->getHeight();
}

bool sdk::Window::isFullScreen() const
{
    return m_pWindow->isFullScreen();
}

void sdk::Window::close()
{
    m_pWindow->close();
}