#pragma once

#include <iostream>

#if defined (_WIN32)
#   if defined(gameEngine_EXPORTS)
#       define  AUDIO_ENGINE_EXPORT __declspec(dllexport)
#   else
#       define  AUDIO_ENGINE_EXPORT __declspec(dllimport)
#   endif /* gameEngine_EXPORTS */
#else /* defined (_WIN32) */
#   define AUDIO_ENGINE_EXPORT
#endif

class AUDIO_ENGINE_EXPORT AudioEngine {
	public:
	AudioEngine() {};

	static int PlayWavMusic(const std::string & filename);
	static int PlayWavSound(const std::string & filename);
};