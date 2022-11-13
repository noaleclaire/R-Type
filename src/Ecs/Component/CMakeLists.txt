set(INCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Component)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Component)

set(SRC
    ${SRC}
    ${SRCROOT}/Position.cpp
    ${SRCROOT}/Clickable.cpp
    ${SRCROOT}/Ammo.cpp
    ${SRCROOT}/Controllable.cpp
    ${SRCROOT}/Killable.cpp
    ${SRCROOT}/Rectangle.cpp
    ${SRCROOT}/Layer.cpp
    ${SRCROOT}/Link.cpp
    ${SRCROOT}/Type.cpp
    ${SRCROOT}/Text.cpp
    ${SRCROOT}/TextBox.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
