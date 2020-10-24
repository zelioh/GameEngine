//
// Created by tangt on 24/10/2020.
//

#include "Window.h"

graphics::Window::Window(HINSTANCE const &hInstance):
m_hInstance(hInstance),
m_hwnd(nullptr),
m_bIsFullScreen(false),
m_iWidth(800),
m_iHeight(600)
{
    LPCWSTR CLASS_NAME = L"myWin32WindowClass";
    WNDCLASS wc{};

    wc.hInstance = m_hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpfnWndProc = WindowProcessMessages;
    RegisterClass(&wc);

    HMONITOR hmon = MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = { sizeof(mi) };
    if (!GetMonitorInfo(hmon, &mi))
    {
        throw std::runtime_error("Enable to get monitor informations");
    }
    m_hwnd = CreateWindow(CLASS_NAME, L"Win32 Tutorial",
    //WS_POPUP          | // FullScreen
                        WS_OVERLAPPED     | // No FullScreen
                        WS_CAPTION        | // No FullScreen
                        WS_SYSMENU        | // No FullScreen
                        WS_THICKFRAME     | // No FullScreen
                        WS_MINIMIZEBOX    | // No FullScreen
                        WS_MAXIMIZEBOX    | // No FullScreen
                        WS_BORDER         | // No FullScreen
                        WS_VISIBLE,			// Window style
                        CW_USEDEFAULT, CW_USEDEFAULT, // Window initial position
                        m_iWidth, m_iHeight, // Window size
                        nullptr, // Parent handle
                        nullptr, // Menu handle
                        m_hInstance, // Current Instance
                        nullptr // Extra parameters
                        );
}

graphics::Window::~Window()
{
    PostQuitMessage(0);
    m_hInstance = nullptr;
    m_hwnd = nullptr;
}

const HINSTANCE & graphics::Window::getHInstance() const
{
    return m_hInstance;
}

const HWND & graphics::Window::getHWindow() const
{
    return m_hwnd;
}

bool graphics::Window::isFullScreen() const
{
    return m_bIsFullScreen;
}

int graphics::Window::getWidth() const
{
    return m_iWidth;
}

int graphics::Window::getHeight() const
{
    return m_iHeight;
}

int graphics::Window::addEventCallback(const EventCallback & callback)
{
    static int id = 0;

    m_callbacks[id] = callback;
    ++id;
    return id - 1;
}

bool graphics::Window::removeEventCallback(int callbackID)
{
    if (m_callbacks.find(callbackID) != m_callbacks.end())
    {
        m_callbacks.erase(callbackID);
        return true;
    }
    return false;
}

graphics::Window::operator bool()
{
    return GetMessage(&m_message, nullptr, 0, 0);
}

void graphics::Window::handleEvent()
{
    TranslateMessage(&m_message);
    DispatchMessage(&m_message);
}

LRESULT graphics::Window::WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam)
{
    ///< TODO: Add events and then call all Callback with event

    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, msg, param, lparam);
    }
}

void graphics::Window::useCallback(int eventID) const
{
    for (auto callback : m_callbacks)
    {
        callback.second(eventID);
    }
}