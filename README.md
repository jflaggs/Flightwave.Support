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
We should now have the cmake folder structure for **Flightwave.App**:
```
Flightwave.App/
├── build/
│   └── Debug/
│   └── Release/
├── src/
│   └── main.cpp
├── CMakeLists.txt
├── conanfile.py
```

## Bumping Package Version

#### Library Side:
1. Modify source/include files in the IDE
2. Version the package in conanfile.py `version = 2.0.0`
3. Rebuild the package `conan create . --build=missing`
4. Verify conan cache `conan list flightwave*`
5. Push source to get `git push`

#### Application Side:
6. Update the conanfile.py `requires = "flightwave/2.0.0"`
7. Reinstall packages:
```
    conan install . -s build_type=Debug --build=missing --output-folder=build/Debug
    conan install . -s build_type=Release --build=missing --output-folder=build/Release
```
8. Rebuild the project 
```
    cmake --build build/Debug --config Debug
    cmake --build build/Release --config Release
```

**Note:** 
- There is no automatic switching between debug/release builds so you'll need to open the projects separately.
- We can use `conan editable` to automatically update the application when we version the library source.


## Future Work
At some point I'd like to migrate the conan packages to [Conan Center](https://conan.io/center) as a remote package similar to [Nuget](https://www.nuget.org/). There is an approval process, but once the library in approved on we can reference the remote package with:

```
    conan remote add conancenter https://center.conan.io
    conan install . -s build_type=Release --build=missing --output-folder=build/Release
    cmake --build build/Release --config Release
```

I've also started some automation workflows using windows scripting (bat) but I think existing tools should be explored further before going further down the path of building my own workflow automation tools. 

Golden Config Files:

The current versions of `conanfile.py` and `CMakeLists.txt` are intended to be maintained and reused as golden files and modified on an as-needed basis. Plan to archive golden files for specific builds. 

## License
This project is licensed under MIT License [LICENSE.md](LICENSE.md).

## References
This readme.md was created with the help of [Markdown Live Preview](https://markdownlivepreview.com/).
