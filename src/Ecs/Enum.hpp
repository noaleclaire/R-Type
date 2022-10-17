/*
** EPITECH PROJECT, 2022
** Enum
** File description:
** Enum
*/

#pragma once

namespace ecs
{
    enum Scenes { MENU, SETTINGS, WIN, LOOSE, LOBBY, GAME };
    enum EntityTypes { SPACESHIP, MONSTER, SHOT, BUTTON, WALL, BACKGROUND };
    enum ComponentTypes { CLICKABLE, COLLIDER, CONTROLLABLE, DRAWABLE, KILLABLE, LAYER, POSITION, RECTANGLE, SHOOTABLE, SHOOTER, TYPE };
} // namespace ecs
