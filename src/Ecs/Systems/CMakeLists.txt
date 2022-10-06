set(INCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Systems)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Systems)

set(SRC
    ${SRC} ${SRCROOT}/Systems.cpp ${INCROOT}/Systems.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
