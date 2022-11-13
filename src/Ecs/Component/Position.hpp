/*
** EPITECH PROJECT, 2022
** Position.hpp
** File description:
** Position.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Position : public AComponent {
      public:
        /**
         * @brief Construct a new Position object
         *
         */
        Position() = default;
        /**
         * @brief Construct a new Position object
         *
         * @param x
         * @param y
         * @param xVelocity
         * @param yVelocity
         */
        Position(float x, float y, float xVelocity = 0, float yVelocity = 0);
        /**
         * @brief Construct a new Position object
         *
         * @param other
         */
        Position(const Position &other) = default;
        /**
         * @brief Destroy the Position object
         *
         */
        ~Position() = default;
        /**
         * @brief
         *
         * @param other
         * @return Position&
         */
        Position &operator=(const Position &other) = default;

        /** Getter */
        /**
         * @brief
         *
         * @return float
         */
        float getXPosition() const;
        /**
         * @brief
         *
         * @return float
         */
        float getYPosition() const;
        /**
         * @brief
         *
         * @return float
         */
        float getXVelocity() const;
        /**
         * @brief
         *
         * @return float
         */
        float getYVelocity() const;

        /** Setter */
        /**
         * @brief
         *
         * @param x
         */
        void setXPosition(float x);
        /**
         * @brief
         *
         * @param y
         */
        void setYPosition(float y);
        /**
         * @brief
         *
         * @param x
         */
        void setXVelocity(float x);
        /**
         * @brief
         *
         * @param y
         */
        void setYVelocity(float y);

        void setRedStart(bool start);
        void setGreenStart(bool start);
        void setBlueStart(bool start);
        void setChangeTarget(bool changeTarget);
        void setRedXPos(float pos);
        void setRedYPos(float pos);
        void setGreenXPos(float pos);
        void setGreenYPos(float pos);
        void setBlueXPos(float pos);
        void setBlueYPos(float pos);

        float getRedXPos();
        float getRedYPos();
        float getGreenXPos();
        float getGreenYPos();
        float getBlueXPos();
        float getBlueYPos();

        bool getRedStart();
        bool getGreenStart();
        bool getBlueStart();
        bool getChangeTarget();
        bool getAngle();
        bool getDoneAngle();

      private:
        float _x;
        float _y;
        float _xVelocity;
        float _yVelocity;
        float _redX;
        float _redY;
        float _greenX;
        float _greenY;
        float _blueX;
        float _blueY;
        bool _redStart = false;
        bool _greenStart = false;
        bool _blueStart = false;
        bool _changeTarget = false;
        bool _angle = false;
        bool _doneAngle = false;
    };
} // namespace ecs
