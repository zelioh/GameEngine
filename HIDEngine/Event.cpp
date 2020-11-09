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

std::pair<int, int> HID::mouse::MouseMove()
{
    static std::pair<int, int> previousPos(-1, -1);
    std::pair<int, int> delta(0, 0);
    std::pair<int, int> currentPosition = GetMousePosition();

    if (previousPos == std::pair<int, int>(-1, -1))
    {
        previousPos = currentPosition;
    }

    if (previousPos != currentPosition)
    {
        delta.first = currentPosition.first - previousPos.first;
        delta.second = currentPosition.second - previousPos.second;
        if (delta.first >= 1)
        {
            delta.first = 1;
            previousPos.first += 1;
        } else if (delta.first <= -1) {
            delta.first = -1;
            previousPos.first -= 1;
        }
        if (delta.second >= 1)
        {
            delta.second = 1;
            previousPos.second += 1;
        }
        if (delta.second <= -1)
        {
            delta.second = -1;
            previousPos.second -= 1;
        }
    }
	return delta;
}
