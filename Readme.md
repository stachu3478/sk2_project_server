# SK2 Project Server

![Build status](https://travis-ci.com/stachu3478/sk2_project_server.svg?branch=main)

## Usage:

### Requirements:
- CMake - minimum version 3.0.0
- GCC compiler - version 9.3.0

### Setup:

- Run command: `cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -H. -B./build -G "Unix Makefiles"`
- CMake files should appear the most of project subdirectories
- Project is ready to complile and running tests

### Build:
- Run command: `cmake --build ./build`
- Executable file should appear such at `./build/sk2_project_server` path

## Run tests:
- In `build` directory
- Run `ctest`