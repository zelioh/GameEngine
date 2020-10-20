Target: Windows 10 x64
Build system: CMake >=3.15

Dependencies:
-portaudio
-cmake >= 3.15

Care you must use BUILD_ALL option to build all dll file.
If you build a specific target it will build only the dll of the selected target.

If you need to regenerate the visual studio sln, you must make the following command in the root dir of the projetc:
  cmake -G "Visual Studio 16 2019".
After the .sln will be create.

Care think to build Core before other
