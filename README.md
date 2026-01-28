## Description

[Flightwave.Support](#) Is a library which implements a producer-consumer message bus wherein messages are guaranteed to be ordered by their respective sequence numbers and are queriable by topic IDs.

This library also demonstrates proficient usage of tooling such as conan, cmake, visual studio, and git; and also demonstrates maintaining separation between library and application on a conceptual and practical basis. 

The following readme is meant to guide you through the process of package management with conan. 

## Prerequisites (Windows)
- [Chocolatey](https://chocolatey.org/install) for windows package management.
- [Visual Studio](https://visualstudio.microsoft.com/vs/community/) for IDE and compiler
- [Python](https://www.python.org/downloads) + `Pip` for conan support 
- [Conan](https://conan.io/downloads) for dependency management 
- [CMake](https://cmake.org/download/) for cross-platform build system creation
- [Git](https://git-scm.com/install/windows) for version control
- [CMD](https://ss64.com/) and/or `PowerShell` for windows scripting

Notes:

*Make sure to allow command line symbols in each installation.*
*Conan can be installed quickly with Pip:*

`pip install --upgrade conan`

Run the following commands to verify installation success:

```
python --version
cmake --version
conan --version
```

## Repos
The projects are separated into implementation and application level repositories. This is to maintain separation between the Message Bus implementation and the calling application logic.  

| Repository             | Description                                      |
| ---------------------- | ------------------------------------------------ |
| Flightwave.Support     | C++ library packaged with Conan                  |
| Flightwave.App         | Consumer application that depends on the library |


First, we build and package the library **Flightwave.Support**:
1. `git clone https://github.com/jflaggs/Flightwave.Support.git`
2. `conan profile detect --force`
3. `conan create . --build=missing`
4. `conan list flightwave*`

The conan cache is now up to date and we should have the CMake folder structure below:

```
Flightwave.Support/
├── cmake/
│   └── FlightwaveConfig.cmake.in
├── include/
│   └── flightwave.h
├── src/
│   └── Flightwave.cpp
├── CMakeLists.txt
├── conanfile.py
```

We can then build the application from **Flightwave.App**:

1. `git clone https://github.com/jflaggs/Flightwave.App.git`

2. Build Debug 
```
    conan install . -s build_type=Debug --build=missing --output-folder=build/Debug
    cmake -S . -B build/Debug -DCMAKE_TOOLCHAIN_FILE="build/Debug/conan_toolchain.cmake"
    cmake --build build/Debug --config Debug
```
3. Build Release
```
    conan install . -s build_type=Release --build=missing --output-folder=build/Release
    cmake -S . -B build/Release -DCMAKE_TOOLCHAIN_FILE="build/Release/conan_toolchain.cmake"
    cmake --build build/Release --config Release
```

## License

This project is licensed under the MIT License [LICENSE.md](#LICENSE.md).
