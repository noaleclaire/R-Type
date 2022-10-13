set(INCROOT ${PROJECT_SOURCE_DIR}/src/client/Sfml)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/client/Sfml)

set(SRC ${SRCROOT}/SpritesManager.cpp ${SRCROOT}/Graphical.cpp)

set(INCDIRS ${INCROOT})

source_group("" FILES ${SRC})

set(LIB_NAME Sfml)

add_library(Sfml ${SRC})

target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})
target_include_directories(Sfml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
