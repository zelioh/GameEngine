//
// Created by tangt on 24/10/2020.
//
// Class to handle Win32 windows
//

#ifndef GAMEENGINE_WINDOW_H
#define GAMEENGINE_WINDOW_H

#include <Windows.h>
#include <functional>
#include "GraphicsEngine.h"

namespace graphics {

    class WindowParameters;

    class GRAPHICS_ENGINE_EXPORT Window
    {
    public:
        using EventCallback = std::function<void(int inputID)>;

        static Window * getInstance();

        ~Window();

        void initialize(const HINSTANCE & hInstance, const WindowParameters & parameters);

        const HINSTANCE & getHInstance() const;
        const HWND & getHWindow() const;
        bool isFullScreen() const;
        int getWidth() const;
        int getHeight() const;

        operator bool(); ///< Check if the window is able to getMessage and so if it open.
        void handleEvent(); ///< Handle event must be call in the game loop

        void close() const;
        void resize(int newWidth, int newHeight);
        bool wasResized() const;
        void setResizeStatus(bool status);

    private:
        Window();
        static LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam); ///< Process event

        DWORD getWindowStyle(const WindowParameters & parameters);
    private:
        HWND m_hwnd;
        HINSTANCE m_hInstance;
        std::unordered_map<int, EventCallback> m_callbacks;
        bool m_bIsFullScreen;
        int m_iWidth;
        int m_iHeight;
        bool m_bWasResize;
        bool m_isInitialize;

        MSG m_message;
    };
}

#endif //GAMEENGINE_WINDOW_H
