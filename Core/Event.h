#pragma once

#include <iostream>
#include <windows.h>


class Event
{
public:
	enum KEY {
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
	bool IsKeyDown(Event::KEY) const;
	bool IsKeyUp(Event::KEY) const;
	bool IsLeftMouseKeyDown() const;
	bool IsRightMouseKeyDown() const;
	bool IsMidleMouseKeyDown() const;
	std::pair<int, int> GetMousePosition() const;
	bool MouseMove() const;
private:
};

