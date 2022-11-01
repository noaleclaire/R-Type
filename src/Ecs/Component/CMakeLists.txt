set(INCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Component)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Component)

set(SRC
    ${SRC}
    ${SRCROOT}/Position.cpp
    ${SRCROOT}/Clickable.cpp
    ${SRCROOT}/Controllable.cpp
    ${SRCROOT}/Shootable.cpp
    ${SRCROOT}/Rectangle.cpp
    ${SRCROOT}/Layer.cpp
    ${SRCROOT}/Type.cpp
    ${SRCROOT}/Text.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
