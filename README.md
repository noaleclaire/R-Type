R-Type Game              {#mainpage}
====

[![License](https://img.shields.io/github/license/MisterPeModder/Arcade)](https://github.com/EpitechPromo2025/B-CPP-500-NAN-5-1-rtype-noa.leclaire)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Shell Script](https://img.shields.io/badge/shell_script-%23121011.svg?style=for-the-badge&logo=gnu-bash&logoColor=white)

R-Type is a horizontally scrolling shooter arcade video game developed and released by Irem in 1987 and the first game in the R-Type series. The player controls a star ship, the R-9 "Arrowhead", in its efforts to destroy the Bydo, a powerful alien race bent on wiping out all of mankind.

![Screenshot_20221113_134843](https://user-images.githubusercontent.com/72009611/201525861-bd45c626-0c75-44ae-a3c6-015a70263b3f.png)


====

## Building

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Fedora](https://img.shields.io/badge/Fedora-294172?style=for-the-badge&logo=fedora&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

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

# Return to previous directory
cd -
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

# Return to previous directory
cd -
```

====
## Launch Game

1- Launch the server

```sh
#build the server on linux
./r_type_server
#build the server on windows
.\r_type_server
```
2- Launch the client

```sh
#build the server on linux
./r_type_client
#build the server on windows
.\r_type_client
```

====

## Package

See the doc: documentation/PACKAGE_DOCUMENTATION.md

====

## Professional Documentation

Required tools:
- Doxygen 1.9.5 (minimum)
  - -> Install link : https://doxygen.nl/manual/install.html

```sh
#build the documentation on linux
./setup_doc.sh
#build the documentation on windows
.\setup_doc.sh
```

====

## Groups

| Group |
|--------------------------------------------------|
| Noa Leclaire <noa.leclaire@epitech.eu> |
| Julien Lafargue   <julien.lafargue@epitech.eu>   |
| Enzo Laurent <enzo.laurent@epitech.eu>  |
| Alexandre Laborde <alexandre.laborde@epitech.eu> |
| Marvin Verain  <marvin.verain@epitech.eu>    |
