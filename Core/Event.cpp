#include "Event.h"

bool Event::IsKeyDown(Event::KEY key) const {
	if (GetKeyState(key) < 0)
		return true;
	return false;
}

bool Event::IsKeyUp(Event::KEY key) const {
	if (GetKeyState(key) >= 0)
		return true;
	return false;
}

bool Event::IsLeftMouseKeyDown() const {
	if (GetAsyncKeyState(VK_LBUTTON) < 0)
		return true;
	return false;
}

bool Event::IsRightMouseKeyDown() const {
	if (GetAsyncKeyState(VK_RBUTTON) < 0)
		return true;
	return false;
}

bool Event::IsMidleMouseKeyDown() const {
	if (GetAsyncKeyState(MK_MBUTTON) < 0)
		return true;
	return false;
}

std::pair<int, int> Event::GetMousePosition() const {
	POINT p;

	GetCursorPos(&p);
	return std::make_pair(p.x, p.y);
}

bool Event::MouseMove() const {
	if (GetKeyState(WM_MOUSEMOVE) < 0)
		return true;
	return false;
}
