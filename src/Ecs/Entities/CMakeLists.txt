set(INCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Entities)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Entities)

set(SRC
    ${SRC} ${SRCROOT}/Entity.cpp ${INCROOT}/Entity.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
