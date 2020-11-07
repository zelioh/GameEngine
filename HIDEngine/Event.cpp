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

std::pair<int, int> HID::mouse::GetMousePosition()
{
	POINT p;

	GetCursorPos(&p);
	return std::make_pair(p.x, p.y);
}

bool HID::mouse::MouseMove()
{
	if (GetKeyState(WM_MOUSEMOVE) < 0)
		return true;
	return false;
}
