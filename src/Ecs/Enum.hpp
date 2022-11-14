/*
** EPITECH PROJECT, 2022
** Enum
** File description:
** Enum
*/

#pragma once
#include <chrono>

#define NB_MAX_PLAYERS_PER_ROOM 4
#define ROOM_ID_SIZE 8
#define DISCONNECTION_TIME 1500
#define SPACESHIP_SPEED 300

namespace ecs
{
    enum Scenes { ROOM1, GAME1, ROOM2, GAME2, ROOM3, GAME3,
                PUBLICROOM, PRIVATEROOM, LISTROOM, JOINROOMBYID, QUITROOM,
                MENU, SETTINGS, WIN, LOOSE, GAME, RETURNTOGAME, TYPEPSEUDO, HOWTOPLAY, ACHIEVEMENTS };
    enum Music { CAVE, SPACE, DESERT, SNOW, FOREST, MUSICMENU, BOSS };

    enum EntityTypes { SPACESHIP, MONSTER, SHOT, BUTTON, WALL, BACKGROUND, PARALLAX, ROOM, ROOMID, ROOMMODE, ROOMPLAYERSNAME, SHAPE, TEXT, TEXTBOX, TEXTBOXNUMBER, PSEUDO, MUSIC, SFX };
    enum AchievementTypes { MATRIX, RAMPAGE, XITING, HACKER, NEMESIS, BFF, WORLDWARRIOR, PAIN, MARVIN };
    class Enum {
        public:
            static std::chrono::time_point<std::chrono::system_clock> ping_latency;
            static int ping_latency_ms;
    };
} // namespace ecs
