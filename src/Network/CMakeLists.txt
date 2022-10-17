set(INCROOT ${PROJECT_SOURCE_DIR}/src/Network/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Network/)

set(SRC ${INCROOT}/Message.hpp)

add_library(Network INTERFACE ${SRC})

target_include_directories(Network INTERFACE ${INCROOT})