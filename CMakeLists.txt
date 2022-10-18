cmake_minimum_required(VERSION 3.17.0)


set(CMAKE_BUILD_TYPE Release)
project(R-Type)

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

if(WIN32)
  add_definitions(/D _CRT_SECURE_NO_WARNINGS)
  add_definitions(/D NOMINMAX)
  add_definitions(/D WIN32_LEAN_AND_MEAN)
  set(GUI_TYPE WIN32)
endif(WIN32)

add_subdirectory(src)
