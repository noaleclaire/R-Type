set(INCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Exceptions)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Exceptions)

set(SRC
    ${SRC}
    ${INCROOT}/Exception.hpp
    ${INCROOT}/ExceptionComponentNull.hpp
    ${INCROOT}/ExceptionEntityUnobtainable.hpp
    ${INCROOT}/ExceptionIndexComponent.hpp
    ${INCROOT}/ExceptionSparseArrayUnobtainable.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
