set(INCROOT ${PROJECT_SOURCE_DIR}/src/server/Ecs/Exceptions)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server/Ecs/Exceptions)

set(SRC
    ${SRC}
    ${INCROOT}/Exception.hpp
    ${INCROOT}/ExceptionComponentNull.hpp
    ${INCROOT}/ExceptionEntityLabelExists.hpp
    ${INCROOT}/ExceptionEntityUnobtainable.hpp
    ${INCROOT}/ExceptionIndexComponent.hpp
    ${INCROOT}/ExceptionSparseArrayUnobtainable.hpp
    PARENT_SCOPE
    )

SET(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE
)