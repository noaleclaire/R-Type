cmake_minimum_required(VERSION 3.17.0)

project(R-Type LANGUAGES CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_compile_options("-Wall" "-pedantic" "$<$<CONFIG:RELEASE>:-O3;>"
                    "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -std=c++2a -Wextra -Wshadow -Wpointer-arith -lpthread"
  )
endif(CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory(src)
