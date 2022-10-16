set(INCROOT ${PROJECT_SOURCE_DIR}/src/server/Network/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server/Network/)

set(SRC ${SRCROOT}/CustomServer.cpp)

set(INCDIRS ${INCROOT})

source_group("" FILES ${SRC})

set(LIB_NAME Network)

add_library(Network ${SRC})

target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})
target_include_directories(Network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
