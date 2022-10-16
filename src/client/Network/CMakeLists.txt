set(INCROOT ${PROJECT_SOURCE_DIR}/src/client/Network/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/client/Network/)

set(SRC ${SRCROOT}/CustomClient.cpp)

set(INCDIRS ${INCROOT})

source_group("" FILES ${SRC})

set(LIB_NAME Client)

add_library(Client ${SRC})

target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})
target_include_directories(Client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
