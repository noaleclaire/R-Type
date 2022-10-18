set(INCROOT ${PROJECT_SOURCE_DIR}/src/client/Sfml)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/client/Sfml)

set(SRC
    ${SRC} ${SRCROOT}/SpritesManager.cpp ${SRCROOT}/Event.cpp
    ${SRCROOT}/Graphical.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
