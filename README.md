R-Type Game              {#mainpage}
====

[![License](https://img.shields.io/github/license/MisterPeModder/Arcade)](https://github.com/EpitechPromo2025/B-CPP-500-NAN-5-1-rtype-noa.leclaire)

R-Type is a horizontally scrolling shooter arcade video game developed and released by Irem in 1987 and the first game in the R-Type series. The player controls a star ship, the R-9 "Arrowhead", in its efforts to destroy the Bydo, a powerful alien race bent on wiping out all of mankind.

![image](https://user-images.githubusercontent.com/72009611/196052229-109475d4-6290-4686-a0b1-7ecf660cd6e1.png)

====

## Building

### Command Line (via CMake)

Confirmation badge for Build and Test:

[![CMake](https://github.com/EpitechPromo2025/B-CPP-500-NAN-5-1-rtype-noa.leclaire/actions/workflows/build_and_test.yaml/badge.svg)](https://github.com/EpitechPromo2025/B-CPP-500-NAN-5-1-rtype-noa.leclaire/actions/workflows/build_and_test.yaml)

Required tools:
- CMake 3.17 (minimum)
    - -> Install link : https://cmake.org/install/

on Linux:
```sh
# Create the build directory and install all tools
./setup_conan.sh


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
./setup_conan.sh

# Configure the project
cmake .. -G 'Visual Studio 17 2022' -DCMAKE_BUILD_TYPE=Release

# Build the executable and libraries
cmake --build .

# Return to previous directory
cd -
```

====

## Professional Documentation

Required tools:
- Doxygen 1.9.5 (minimum)
  - -> Install link : https://doxygen.nl/manual/install.html

```sh
#build the documentation
doxygen doxyfile

#open the documentation
xdg-open docs/html/index.html
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
