//
// Created by FiercePC on 10/11/2020.
//

#include "WindowEvent.h"

HID::WindowEvent * HID::WindowEvent::getInstance()
{
    static WindowEvent * windowEvent = nullptr;

    if (nullptr == windowEvent)
    {
        windowEvent = new WindowEvent();
    }
    return windowEvent;
}

void HID::WindowEvent::registerKeyPressCallback(const std::string &levelIdentifier, const KeyCallback &function)
{
    m_vKeyCallbacks[levelIdentifier] = function;
}

void HID::WindowEvent::registerMouseCallback(const std::string &levelIdentifier, const MouseCallback &function)
{
    m_vMouseCallbacks[levelIdentifier] = function;
}

void HID::WindowEvent::registerWindowCallback(const WindowCallback &function)
{
    m_vWindowCallbacks = function;
}

void HID::WindowEvent::onKeyPress(const std::string &levelIdentifier, keyboard::Event id, bool isKeyUp)
{
    if (m_vKeyCallbacks[levelIdentifier])
    {
        m_vKeyCallbacks[levelIdentifier](id, isKeyUp);
    }
}

void HID::WindowEvent::onMouseEvent(const std::string &levelIdentifier,
                                    mouse::Event id,
                                    int x, int y,
                                    int scrollDelta)
{
    if (m_vMouseCallbacks[levelIdentifier]) {
        m_vMouseCallbacks[levelIdentifier](id, x, y, scrollDelta);
    }
}

void HID::WindowEvent::onWindowEvent(window::Event id, int width, int height)
{
    if (m_vWindowCallbacks)
    {
        m_vWindowCallbacks(id, width, height);
    }
}