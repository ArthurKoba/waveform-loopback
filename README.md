# waveform-loopback

Simple example of using [Loopback Recording](https://learn.microsoft.com/en-us/windows/win32/coreaudio/loopback-recording).

You can build the project with either the MSVC compiler or with WSL through cross-compiling.

## Prerequisites
- CMake
- Visual Studio
- WSL & mingw-w64 (Only For Cross-Compiling)

## Build Setup
1. Download prebuilt GLFW binaries from [here](https://www.glfw.org/download). 
2. Extract the GLFW binaries for your build to `external/glfw`.
    - For Windows, extract the binaries from the correct folder corresponding to your Visual Studio version.
    - For WSL, just extract the binaries from `lib-mingw-w64`.
3. Extract the GLFW headers (the entire `include` folder) to `external/glfw`.
4. For WSL, install mingw-w64 if you haven't already. 
    - For Ubuntu, just run `sudo apt-get install gcc-mingw-w64`.

## Building Instructions
Run `build.bat` from Windows or `build.sh` on WSL.
