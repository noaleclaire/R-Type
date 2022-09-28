set(INCROOT ${PROJECT_SOURCE_DIR}/src/server/Ecs/Entities)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server/Ecs/Entities)

set(SRC
    ${SRC}
    ${SRCROOT}/Entity.cpp
    ${INCROOT}/Entity.hpp
    PARENT_SCOPE
    )

SET(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE
)