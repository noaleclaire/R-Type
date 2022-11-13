# Package Documentation {#page_three}

## Building

### Command Line (via CMake)

Required tools:
- CMake 3.17 (minimum) ![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
    - -> Install link : https://cmake.org/install/

On Linux:  

```sh
# Create the build directory and install all tools
chmod 755 setup.conan.sh
./setup_conan.sh


# Configure the project
cmake .. -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Release

# Build the executable and libraries
cmake --build .

#Build the package
cpack
```

On Windows:

  Required tools:  
  - Conan  
    -> Install link : https://github.com/conan-io/conan/releases/latest/download/conan-win-64.exe
  - Visual Studio 2017  
    -> Install link : https://my.visualstudio.com/Downloads?q=visual%20studio%202017&wt.mc_id=o~msft~vscom~older-downloads

```sh
# Create the build directory
chmod +x setup.conan.sh
./setup_conan.sh

# Configure the project
cmake . -G "Visual Studio 15 2017" -DCMAKE_BUILD_TYPE=Release -A x64

# Build the executable and libraries
cmake --build . --config Release

#Build the package
cpack -C ZIP --release
```

You can find packge with .sh, .tar.Z, .tar.gz, .tar.zip
