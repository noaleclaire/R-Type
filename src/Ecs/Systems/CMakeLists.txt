set(INCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Systems)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Systems)

set(SRC
    ${SRC} ${SRCROOT}/Systems.cpp ${INCROOT}/Systems.hpp
           ${SRCROOT}/SystemsServer.cpp ${INCROOT}/SystemsServer.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
