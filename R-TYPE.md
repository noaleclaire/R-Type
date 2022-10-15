LAUNCH GAME                 {#mainpage}
====

### Building

========

### Command Line (via CMake)

Confirmation badge for Build and Test:

[![CMake](https://github.com/EpitechPromo2025/B-CPP-500-NAN-5-1-rtype-noa.leclaire/actions/workflows/build_and_test.yaml/badge.svg)](https://github.com/EpitechPromo2025/B-CPP-500-NAN-5-1-rtype-noa.leclaire/actions/workflows/build_and_test.yaml)

Required tools:
- CMake 3.17 (minimum)

on Linux:
```sh
# Create the build directory
mkdir build && cd build

# Install Conan
pip install conan --user
conan install .. -c tools.system.package_manager:mode=install
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install .. --build missing

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