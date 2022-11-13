/*
** EPITECH PROJECT, 2022
** Position.cpp
** File description:
** Position.cpp
*/

#include "Position.hpp"

namespace ecs
{
    Position::Position(float x, float y, float xVelocity, float yVelocity) : _x(x), _y(y), _xVelocity(xVelocity), _yVelocity(yVelocity)
    {
    }

    /** Getter */
    float Position::getXPosition() const
    {
        return _x;
    }
    float Position::getYPosition() const
    {
        return _y;
    }

    float Position::getXVelocity() const
    {
        return _xVelocity;
    }

    float Position::getYVelocity() const
    {
        return _yVelocity;
    }

    /* Setter */
    void Position::setXPosition(float x)
    {
        _x = x;
    }

    void Position::setYPosition(float y)
    {
        _y = y;
    }

    void Position::setXVelocity(float x)
    {
        _xVelocity = x;
    }

    void Position::setYVelocity(float y)
    {
        _yVelocity = y;
    }

    void Position::setRedStart(bool start)
    {
        _redStart = start;
    }

    void Position::setGreenStart(bool start)
    {
        _greenStart = start;
    }

    void Position::setBlueStart(bool start)
    {
        _blueStart = start;
    }

    void Position::setChangeTarget(bool changeTarget)
    {
        _changeTarget = changeTarget;
    }

    void Position::setRedXPos(float pos)
    {
        _redX = pos;
    }

    void Position::setRedYPos(float pos)
    {
        _redY = pos;
    }

    void Position::setGreenXPos(float pos)
    {
        _greenX = pos;
    }

    void Position::setGreenYPos(float pos)
    {
        _greenY = pos;
    }

    void Position::setBlueXPos(float pos)
    {
        _blueX = pos;
    }

    void Position::setBlueYPos(float pos)
    {
        _blueY = pos;
    }

    bool Position::getRedStart()
    {
        return _redStart;
    }

    bool Position::getGreenStart()
    {
        return _greenStart;
    }

    bool Position::getBlueStart()
    {
        return _blueStart;
    }

    bool Position::getChangeTarget()
    {
        return _changeTarget;
    }

    float Position::getRedXPos()
    {
        return _redX;
    }

    float Position::getRedYPos()
    {
        return _redY;
    }

    float Position::getGreenXPos()
    {
        return _greenX;
    }

    float Position::getGreenYPos()
    {
        return _greenY;
    }

    float Position::getBlueXPos()
    {
        return _blueX;
    }

    float Position::getBlueYPos()
    {
        return _blueY;
    }

    bool Position::getAngle()
    {
        return _angle;
    }

    bool Position::getDoneAngle()
    {
        return _doneAngle;
    }

} // namespace ecs
