//
// Created by FiercePC on 11/11/2020.
//

#ifndef GAMEENGINE_SDK_WINDOW_H
#define GAMEENGINE_SDK_WINDOW_H

#include <windows.h>

namespace graphics
{
    class Window;
}

namespace sdk {

    class Window
    {
    public:
        Window();

        HWND getHWindow() const;
        bool isFullScreen() const;
        int getWidth() const;
        int getHeight() const;

    private:
        graphics::Window * m_pWindow;
    };

}

#endif //GAMEENGINE_WINDOW_H
