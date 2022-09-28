set(INCROOT ${PROJECT_SOURCE_DIR}/src/server/Ecs)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server/Ecs)

set(SRC
    ${SRCROOT}/ecs.cpp
    ${SRCROOT}/ecs.hpp
    ${SRCROOT}/Registry.hpp
    )

add_subdirectory(Systems)
add_subdirectory(Exceptions)
add_subdirectory(Entities)
add_subdirectory(Component)

source_group("" FILES ${SRC})

set(LIB_NAME Ecs)

add_library(Ecs ${SRC})

target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})
target_include_directories(Ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})