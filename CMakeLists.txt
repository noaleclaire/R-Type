cmake_minimum_required(VERSION 3.17.0)

project(R-Type LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()

add_compile_options("-Wall" "-pedantic" "$<$<CONFIG:RELEASE>:-O3;-lsfml-graphics -lsfml-window -lsfml-system>"
                    "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb;-lsfml-graphics -lsfml-window -lsfml-system>")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -std=c++2a -Wextra -Wshadow -Wpointer-arith -lpthread -lsfml-graphics -lsfml-window -lsfml-system"
  )
endif(CMAKE_COMPILER_IS_GNUCXX)

install(FILES ${PROJECT_SOURCE_DIR}/setup_server.sh DESTINATION bin)
install(FILES ${PROJECT_SOURCE_DIR}/setup_server.bat DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/server/levels/ DESTINATION bin/src/server/levels/)
install(FILES ${PROJECT_SOURCE_DIR}/conanfile.txt DESTINATION setup)
install(FILES ${PROJECT_SOURCE_DIR}/setup_conan.sh DESTINATION setup)

include(InstallRequiredSystemLibraries)
set(CPACK_RESSOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_NAME "R-type")
set(CPACK_PACKAGE_VERSION_MAJOR)
set(CPACK_PACKAGE_VERSION_MINOR)
include(CPack)

add_subdirectory(src)
