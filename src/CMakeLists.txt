set(INCROOTSRV ${PROJECT_SOURCE_DIR}/src/server)
set(SRCROOTSRV ${PROJECT_SOURCE_DIR}/src/server)

set(INCROOTCLT ${PROJECT_SOURCE_DIR}/src/client)
set(SRCROOTCLT ${PROJECT_SOURCE_DIR}/src/client)

add_subdirectory(client)
add_subdirectory(server)

set(TARGET_NAME_SERVER r-type_server)
set(TARGET_NAME_CLIENT r-type_client)

add_executable(${TARGET_NAME_SERVER} ${SRCROOTSRV}/main.cpp)
add_executable(${TARGET_NAME_CLIENT} ${SRCROOTCLT}/main.cpp)

add_custom_command(
  TARGET ${TARGET_NAME_SERVER}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME_SERVER}>
          ${PROJECT_SOURCE_DIR})

add_custom_command(
  TARGET ${TARGET_NAME_CLIENT}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME_CLIENT}>
          ${PROJECT_SOURCE_DIR})
