//
// Created by tangt on 24/10/2020.
//
// Class to handle Win32 windows
//

#ifndef GAMEENGINE_WINDOW_H
#define GAMEENGINE_WINDOW_H

#include <windows.h>
#include <functional>

namespace graphics {

    class WindowParameters;

    class Window
    {
    public:
        using EventCallback = std::function<void(int inputID)>;

        Window(const HINSTANCE & hInstance, const WindowParameters & parameters);
        ~Window();

        const HINSTANCE & getHInstance() const;
        const HWND & getHWindow() const;
        bool isFullScreen() const;
        int getWidth() const;
        int getHeight() const;

        /**
         * Add a callback function call when a event occured and the return id of that callback in the pool.
         * The id is use for remove the callback
         * @param callback  callback to add
         * @return id of the callback in the map
         */
        int addEventCallback(const EventCallback & callback);
        /**
         * Remove a callback with it id. The id is obtain when the callback is added
         * @param callbackID id of the callback
         * @return  true if the callback was find and so removed else false
         */
        bool removeEventCallback(int callbackID);

        operator bool(); ///< Check if the window is able to getMessage and so if it open.
        void handleEvent(); ///< Handle event must be call in the game loop

        void close();

    private:
        static LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam); ///< Process event

        void useCallback(int eventID) const; ///< Call all callBack with an eventID ///< TODO: eventID must be a Enum
        DWORD getWindowStyle(const WindowParameters & parameters);
    private:
        HWND m_hwnd;
        HINSTANCE m_hInstance;
        std::unordered_map<int, EventCallback> m_callbacks;
        bool m_bIsFullScreen;
        int m_iWidth;
        int m_iHeight;

        MSG m_message;
    };
}

#endif //GAMEENGINE_WINDOW_H
