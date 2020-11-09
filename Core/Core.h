// Core.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

// TODO: Reference additional headers your program requires here.
class Core {

public:

	Core();
	~Core();

	void Start();
	void Stop();

private:

	bool m_isRunning;
	double _m_frametime;
	// reference graphique engine
	//reference window
	// reference game

};