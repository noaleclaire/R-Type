set(INCROOT ${PROJECT_SOURCE_DIR}/src/client/Sfml)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/client/Sfml)

set(SRC
    ${SRC}
    ${SRCROOT}/SpritesManager.cpp 
    ${SRCROOT}/Graphical.cpp
    ${INCROOT}/SpritesManager.hpp 
    ${INCROOT}/Graphical.hpp
    PARENT_SCOPE
    )

SET(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE
)

