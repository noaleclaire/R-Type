set(INCROOT ${PROJECT_SOURCE_DIR}/src/client/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/client/)

set(SRC ${SRCROOT}/main.cpp)

add_subdirectory(Sfml)
add_subdirectory(Network)

set(TARGET_NAME r-type_client)

add_executable(${TARGET_NAME} ${SRC})

target_link_libraries(${TARGET_NAME} Client)
target_link_libraries(${TARGET_NAME} Sfml)
target_link_libraries(${TARGET_NAME} Ecs)

add_custom_command(
  TARGET ${TARGET_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}>
          ${PROJECT_SOURCE_DIR})
