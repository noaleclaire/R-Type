set(INCROOT ${PROJECT_SOURCE_DIR}/src)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(ECS)

set(TARGET_NAME r-type_server)

add_executable(${TARGET_NAME} ${SRCROOT}/main.cpp)

add_custom_command(
  TARGET ${TARGET_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}>
          ${PROJECT_SOURCE_DIR})
