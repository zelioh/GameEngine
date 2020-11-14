#include "AudioEngine.h"
#include <Windows.h>
#include <istream>
#include <fstream>
#include <algorithm>

using namespace std;

int AudioEngine::PlayWavMusic(const std::string& filename) {
    char buf[BUFSIZ];

    GetCurrentDirectory(BUFSIZ, buf);

    std::string file = buf;
    file += "\\" + filename;

    for (int i = 0; i < file.size(); ++i)
    {
        if (file[i] == '\\')
        {
            file.replace(file.begin() + i, file.begin() + i + 1, "\\\\");
            i++;
        }
    }

    std::cout << file << std::endl;

    PlaySound(file.c_str(), 0, SND_FILENAME | SND_SYNC);
    std::cout << "Hello, World!" << std::endl;

	return TRUE;
}
int AudioEngine::PlayWavSound(const std::string &filename)
{
    return (PlaySound(TEXT(filename.c_str()), NULL, SND_FILENAME));
}