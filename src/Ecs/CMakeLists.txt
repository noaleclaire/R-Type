set(INCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/)

set(SRC)

add_subdirectory(Systems)
add_subdirectory(Exceptions)
add_subdirectory(Entities)
add_subdirectory(Component)

source_group("" FILES ${SRC})

set(LIB_NAME Ecs)

add_library(${LIB_NAME} ${SRC})

target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})
target_include_directories(Ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
