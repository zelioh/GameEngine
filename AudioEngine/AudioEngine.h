#pragma once

#include <iostream>


class AudioEngine {
	public:
	AudioEngine() {};
	int PlayWav(const std::string &filename);
};