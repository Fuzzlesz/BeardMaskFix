Hides beards when wearing items with slot 44.

Port of original mod by Parapets to Skyrim version 1.5.97.

## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++

## Register Visual Studio as a Generator
* Open `x64 Native Tools Command Prompt`
* Run `cmake`
* Close the cmd window

## Building
```
git clone https://github.com/Fuzzlesz/BeardMaskFix-1.5
cd BeardMaskFix-1.5
git submodule init
git submodule update
cmake --preset vs2022-windows
cmake --build build --config Release
```
