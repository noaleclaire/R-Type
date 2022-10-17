set(INCROOT ${PROJECT_SOURCE_DIR}/src/server/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server/)

set(SRC ${SRCROOT}/main.cpp)

add_subdirectory(Network)

source_group("" FILES ${SRC})

set(TARGET_NAME r-type_server)

add_executable(${TARGET_NAME} ${SRC})

target_link_libraries(${TARGET_NAME} Network)
target_link_libraries(${TARGET_NAME} Ecs)
target_link_libraries(${TARGET_NAME} Utilities)
target_link_libraries(${TARGET_NAME} ${CONAN_LIBS})

add_custom_command(
  TARGET ${TARGET_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}>
          ${PROJECT_SOURCE_DIR})
