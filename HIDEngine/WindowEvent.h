//
// Created by FiercePC on 10/11/2020.
//

#ifndef GAMEENGINE_WINDOWEVENT_H
#define GAMEENGINE_WINDOWEVENT_H

#include <functional>
#include <unordered_map>
#include <Windows.h>

#include "HIDEngine.h"

namespace graphics
{
    class Window;
}

namespace HID {

    namespace keyboard
    {
        enum class Event {
            A = 'A',
            B = 'B',
            C = 'C',
            D = 'D',
            E = 'E',
            F = 'F',
            G = 'G',
            H = 'H',
            I = 'I',
            J = 'J',
            K = 'K',
            L = 'L',
            M = 'M',
            N = 'N',
            O = 'O',
            P = 'P',
            Q = 'Q',
            R = 'R',
            S = 'S',
            T = 'T',
            U = 'U',
            V = 'V',
            W = 'W',
            X = 'X',
            Y = 'Y',
            Z = 'Z',
            NUM0 = VK_NUMPAD0,
            NUM1 = VK_NUMPAD1,
            NUM2 = VK_NUMPAD2,
            NUM3 = VK_NUMPAD3,
            NUM4 = VK_NUMPAD4,
            NUM5 = VK_NUMPAD5,
            NUM6 = VK_NUMPAD6,
            NUM7 = VK_NUMPAD7,
            NUM8 = VK_NUMPAD8,
            NUM9 = VK_NUMPAD9,
            SPACE = VK_SPACE,
            SHIFT = VK_SHIFT,
            CONTROL = VK_CONTROL,
            ESCAPE = VK_ESCAPE,
            LEFT = VK_LEFT,
            RIGHT = VK_RIGHT,
            UP = VK_UP,
            DOWN = VK_DOWN,
            TAB = VK_TAB,
        };
    }

    namespace mouse
    {
        enum class Event
        {
            MOUSE_MOVE,
            RIGHT_CLICK,
            LEFT_CLICK,
            MIDDLE_CLICK,
            SCROLL
        };
    };

    namespace window
    {
        enum  class Event
        {
            RESIZE
        };
    };

    /*
     * Currently doesn't work better to use Event.h
     */
    class HID_EXPORT WindowEvent
    {

        friend class graphics::Window;

    public:
        using KeyCallback = std::function<void(keyboard::Event, bool keyUp)>;
        using MouseCallback = std::function<void(mouse::Event event, int x, int y, int scrollDelta)>;
        using WindowCallback = std::function<void(window::Event, int width, int height)>;

        static WindowEvent * getInstance();

        void registerKeyPressCallback(const std::string & levelIdentifier, const KeyCallback & function);
        void registerMouseCallback(const std::string & levelIdentifier, const MouseCallback & function);
        void registerWindowCallback(const WindowCallback & function);

    private:
        WindowEvent() = default;

        void onKeyPress(const std::string & levelIdentifier, keyboard::Event id, bool isKeyUp);
        void onMouseEvent(const std::string & levelIdentifier, mouse::Event id, int x, int y, int scrollDelta);
        void onWindowEvent(window::Event id, int width, int height);

        std::unordered_map<std::string, KeyCallback> m_vKeyCallbacks;
        std::unordered_map<std::string, MouseCallback> m_vMouseCallbacks;
        WindowCallback m_vWindowCallbacks;
    };

}

#endif //GAMEENGINE_WINDOWEVENT_H
