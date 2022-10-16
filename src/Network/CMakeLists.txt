set(INCROOT ${PROJECT_SOURCE_DIR}/src/Network/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Network/)

set(SRC)

source_group("" FILES ${SRC})

set(LIB_NAME Network)

add_library(${LIB_NAME} ${SRC})

target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})
target_include_directories(Network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
