set(INCROOT ${PROJECT_SOURCE_DIR}/src/server/Ecs/Systems)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server/Ecs/Systems)

set(SRC
    ${SRC}
    ${SRCROOT}/Systems.cpp
    ${INCROOT}/Systems.hpp
    PARENT_SCOPE
    )

SET(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE
)