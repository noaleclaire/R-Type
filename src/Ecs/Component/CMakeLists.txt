set(INCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Component)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Ecs/Component)

set(SRC
    ${SRC}
    ${INCROOT}/Collider.hpp
    ${INCROOT}/Controllable.hpp
    ${INCROOT}/Drawable.hpp
    ${INCROOT}/Killable.hpp
    ${INCROOT}/Position.hpp
    ${SRCROOT}/Position.cpp
    ${INCROOT}/Shootable.hpp
    ${SRCROOT}/Shootable.cpp
    ${INCROOT}/Shooter.hpp
    ${INCROOT}/SparseArray.hpp
    ${INCROOT}/Velocity.hpp
    ${SRCROOT}/Velocity.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
