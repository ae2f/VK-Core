# ae2fVK::Core

> Rel-v5.15.22

> This project has been migrated to [codeberg.org](https://codeberg.org/ae2f/VK-Core).  
> You will still be able to access to upstream with github page.

Vulkan SDK with [glslang | clspv]

# Warning
> Setting glslang and clspv on alltogether would cause configuration step failure.  
> This is the flaw of this repository, not yours in high possibility.  

# Test
Build & Run (Ubuntu only): [![ae2f-workflow](https://github.com/ae2f/VK-Core/actions/workflows/cmake-multi-platform.yml/badge.svg?branch=main)](https://github.com/ae2f/VK-Core/actions/workflows/cmake-multi-platform.yml)
> Other Operating systems than Ubuntu are expected to run this library, 
> but will not be tested by github actions due to the lack of support of installation of Vulkan Driver.

# Dependency
> These are necessary, or you will not able to build it.

- C>=90
- C++>=17
- clang
- cmake
- Vulkan SDK
- Vulkan Driver

# Optional dependency
> This will be automatically fetched when not found.  
> Recommended to install for reducing the build time.

- glslang

# Clang
> Clang is the tested compiler which is able to build this project on Linux and Windows.  
> On linux, you could build them also with gcc/g++.

# Windows 11 arm
> Currently has flaw of exit code 0xc000007b.  
