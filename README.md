====

# BUILDING

## Command Line (via CMake)

Confirmation badge for Build and Test:

https://github.com/noa.leclaire/B-CPP-500-NAN-5-1-rtype-noa.leclaire/actions/workflows/.github/workflows/build_and_test.yml/badge.svg

Required tools:
- CMake 3.17 (minimum)

on Linux:
```sh
# Create the build directory
mkdir build && cd build

# Install Conan
conan install . --build missing

# Configure the project
cmake .. -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Release

# Build the executable and libraries
cmake --build .

# Return to previous directory
cd -
```

on Windows:
```sh
# Create the build directory
mkdir build && cd build

# Configure the project
cmake .. -G 'Visual Studio 17 2022' -DCMAKE_BUILD_TYPE=Release

# Build the executable and libraries
cmake --build .

# Return to previous directory
cd -
```
