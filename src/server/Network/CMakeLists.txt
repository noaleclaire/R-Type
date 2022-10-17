set(INCROOT ${PROJECT_SOURCE_DIR}/src/server/Network/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server/Network/)

set(SRC
    ${SRC}
    ${SRCROOT}/CustomServer.cpp
    ${INCROOT}/CustomServer.hpp
    PARENT_SCOPE
    )

SET(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE
)
