#include "Event.h"
#include "WinUser.h"

bool HID::keyboard::IsKeyDown(KEY key)
{
	if (GetKeyState(static_cast<int>(key)) < 0)
		return true;
	return false;
}

bool HID::keyboard::IsKeyUp(KEY key)
{
	if (GetKeyState(static_cast<int>(key)) >= 0)
		return true;
	return false;
}

bool HID::mouse::IsLeftMouseKeyDown()
{
	if (GetAsyncKeyState(VK_LBUTTON) < 0)
		return true;
	return false;
}

bool HID::mouse::IsRightMouseKeyDown()
{
	if (GetAsyncKeyState(VK_RBUTTON) < 0)
		return true;
	return false;
}

bool HID::mouse::IsMidleMouseKeyDown()
{
	if (GetAsyncKeyState(MK_MBUTTON) < 0)
		return true;
	return false;
}

std::pair<int, int> HID::mouse::GetMousePosition(HWND hwnd)
{
	POINT p;

	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
    return std::make_pair(p.x, p.y);
}

std::pair<int, int> HID::mouse::MouseMove(HWND hwnd)
{
    std::pair<int, int> delta(0, 0);
    std::pair<int, int> currentPosition = GetMousePosition(hwnd);
    RECT screenRect;

    GetWindowRect(hwnd, &screenRect);

    int centerX = screenRect.right / 2;
    int centerY = screenRect.bottom / 2;

    delta.first = centerX - currentPosition.first;
    delta.second = centerY - currentPosition.second;
	return delta;
}
