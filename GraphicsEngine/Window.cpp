//
// Created by tangt on 24/10/2020.
//

#include "Window.h"
#include "WindowParameters.h"
#include <stdexcept>
#include "WinUser.h"
#include "WindowEvent.h"
#include "Objects/SceneManager.h"
#include "Windowsx.h"

graphics::Window::Window(HINSTANCE const &hInstance, const WindowParameters & parameters):
m_hInstance(hInstance),
m_hwnd(nullptr),
m_bIsFullScreen(parameters.m_bIsFullScreen),
m_iWidth(parameters.m_iWidth),
m_iHeight(parameters.m_iHeight)
{
    LPCWSTR CLASS_NAME = L"Window";
    WNDCLASS wc{};

    wc.hInstance = m_hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpfnWndProc = WindowProcessMessages;
    RegisterClass(&wc);

    //
    // Get monitor information
    HMONITOR hmon = MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = { sizeof(mi) };
    if (!GetMonitorInfo(hmon, &mi))
    {
        throw std::runtime_error("Enable to get monitor informations");
    }

    //
    // Set size correctly
    {
        m_iWidth = (m_iWidth > (mi.rcMonitor.right - mi.rcMonitor.left)) ? mi.rcMonitor.right - mi.rcMonitor.left
                                                                         : m_iWidth;
        m_iHeight = (m_iHeight > (mi.rcMonitor.bottom - mi.rcMonitor.top)) ? mi.rcMonitor.bottom - mi.rcMonitor.top
                                                                           : m_iHeight;
    }
    int left = (parameters.m_bIsFullScreen) ? mi.rcMonitor.left : parameters.m_iLeft;
    int top = (parameters.m_bIsFullScreen) ? mi.rcMonitor.top : parameters.m_iTop;
    std::wstring szname(parameters.m_strName.begin(), parameters.m_strName.end());

    m_hwnd = CreateWindow(CLASS_NAME, szname.c_str(),
                        getWindowStyle(parameters),
                        left, top, // Window initial position
                        m_iWidth, m_iHeight, // Window size
                        nullptr, // Parent handle
                        nullptr, // Menu handle
                        m_hInstance, // Current Instance
                        nullptr // Extra parameters
                        );

    if (parameters.m_bClipCursorToWindow)
    {
        RECT _clip;

        GetWindowRect(m_hwnd, &_clip);

        //Clip the RECT
        ClipCursor(&_clip);
        SetCursorPos(_clip.right / 2, _clip.bottom / 2);
        ShowCursor(true);
    }
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

graphics::Window::operator bool()
{
    return GetMessage(&m_message, nullptr, 0, 0);
}

void graphics::Window::handleEvent()
{
    TranslateMessage(&m_message);
    DispatchMessage(&m_message);
    InvalidateRect(m_hwnd, NULL, FALSE );   // invalidate whole window
}

void graphics::Window::close() const
{
    DestroyWindow(m_hwnd);
}

LRESULT graphics::Window::WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam)
{
    HID::WindowEvent * windowEvent = HID::WindowEvent::getInstance();
    const std::string & levelIdentifier = object::SceneManager::getInstance()->getCurrentSceneIdentifier();

    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            windowEvent->onKeyPress(levelIdentifier, static_cast<HID::keyboard::Event>(param), false);
            break;
        case WM_KEYUP:
            windowEvent->onKeyPress(levelIdentifier, static_cast<HID::keyboard::Event>(param), true);
            break;
        case WM_LBUTTONDOWN:
            windowEvent->onMouseEvent(levelIdentifier,
                                      HID::mouse::Event::LEFT_CLICK,
                                      GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam), 0);
            break;
        case WM_RBUTTONDOWN:
            windowEvent->onMouseEvent(levelIdentifier,
                                      HID::mouse::Event::RIGHT_CLICK,
                                      GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam), 0);
            break;
        case WM_MBUTTONDOWN:
            windowEvent->onMouseEvent(levelIdentifier,
                                      HID::mouse::Event::MIDDLE_CLICK,
                                      GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam), 0);
            break;

        case WM_MOUSEWHEEL:
            windowEvent->onMouseEvent(levelIdentifier,
                                      HID::mouse::Event::SCROLL,
                                      GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam),
                                      GET_WHEEL_DELTA_WPARAM(param));
            break;

        case WM_MOUSEMOVE:
            windowEvent->onMouseEvent(levelIdentifier,HID::mouse::Event::MOUSE_MOVE,
                                      GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam),
                                      0);
            break;

        case WM_SIZE:
            windowEvent->onWindowEvent(HID::window::Event::RESIZE, LOWORD(lparam), HIWORD(lparam));
            break;

        default:
            return DefWindowProc(hwnd, msg, param, lparam);
    }
    return 0;
}

DWORD graphics::Window::getWindowStyle(const WindowParameters &parameters)
{
    DWORD style = WS_VISIBLE;

    if (parameters.m_bIsFullScreen)
    {
        style |= WS_POPUP;
        return style;
    } else {
        style |= WS_OVERLAPPEDWINDOW;
    }

    if (parameters.m_bCanMinize)
    {
        style |= WS_MINIMIZEBOX;
    }

    if (parameters.m_bCanMaximaze)
    {
        style |= WS_MAXIMIZEBOX;
    }

    if (parameters.m_bIsBorderLess)
    {
        style &= ~WS_BORDER;
    } else {
        style |= WS_BORDER;
    }

    if (parameters.m_bCanResize)
    {
        style |= WS_THICKFRAME;
    } else {
        style &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
    }

    if (parameters.m_bHasSysMenu)
    {
        style |= WS_SYSMENU;
    } else {
        style &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
    }

    if (parameters.m_bHasTitleBar)
    {
        style |= WS_CAPTION;
    } else {
        style &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
    }
    return style;
}