# Project Cowboy Wizard

This repo hosts a small sample game using various technologies without relying on any certain already established game
engine (Unity, Unreal Engine, Hazel, among others).

## Setup

### Prerequisites

- Install [vcpkg](https://vcpkg.io/);
	- **Note**: when installing vcpkg, if on windows, clone the repo into a folder with a small path to avoid
	potential problems (in their early tutorial they specified `C:\\dev\\vcpkg`);
- Install [cmake](https://cmake.org/);
- Install [ninja-build](https://ninja-build.org/).

I assume you have already installed your OS's "default" compiler (MSVC on windows, GCC/Clang on linux, Clang on MacOS).
Further, I assume you're attempting to compile with said compiler. I haven't messed up with attempting to compile with
MinGW on windows, but I'd expect the normal compilation routines would apply.

### Compiling and building

With the power of cmake presets it is too easy!

```bash
# This assumes the environment variable VCPKG_ROOT to be set to the folder where you cloned vcpkg to.
# Setup cmake's cache
cmake -S . -B cmake-build-<build_type> --preset=<build_type>_<operating_system>
# Build!
cmake --build cmake-build-<build_type> --target install
# ???
# Profit! (but this is my game k thx bai) :D
```

The game should be present in the `build/` folder inside this project's root folder.

## Dependencies

This project's dependencies are all listed in the `vcpkg.json` in the root of the repository. Save for any exceptions
where dependencies aren't present in vcpkg's main repository, which will appear here if they become required.