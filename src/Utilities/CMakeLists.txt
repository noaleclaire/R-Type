set(INCROOT ${PROJECT_SOURCE_DIR}/src/Utilities/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Utilities/)

set(SRC ${SRCROOT}/UnpackVariadic.cpp ${SRCROOT}/ParserYaml.cpp
        ${SRCROOT}/AYamlConfig.cpp)

source_group("" FILES ${SRC})

set(LIB_NAME Utilities)

add_library(${LIB_NAME} ${SRC})

target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})
target_include_directories(Utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
