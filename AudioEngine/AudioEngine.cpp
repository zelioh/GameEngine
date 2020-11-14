#include "AudioEngine.h"
#include <Windows.h>

using namespace std;

int AudioEngine::PlayWav(const std::string& filename) {
	return (PlaySound(TEXT(filename.c_str()), NULL, SND_ALIAS));
}