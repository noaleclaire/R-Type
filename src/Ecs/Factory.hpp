/*
** EPITECH PROJECT, 2022
** Factory.hpp
** File description:
** Factory.hpp
*/

#pragma once

#include <map>
#include <cstdarg>
#include "Registry.hpp"
#include "Exceptions/Exception.hpp"
#include "../Utilities/UnpackVariadic.hpp"

namespace ecs
{
    class Factory {
      public:
        typedef std::function<Entity (Registry &)> fptr;
        typedef std::map<EntityTypes, fptr> MapCall;
        template <class... Params>
        static Entity createEntity(Registry &registry, EntityTypes entityType, Params &&...args)
        {
            MapCall creator = {{EntityTypes::SPACESHIP, &createSpaceship}, {EntityTypes::MONSTER, &createMonster},
                                {EntityTypes::SHOT, &createShot}, {EntityTypes::BUTTON, &createButton},
                                {EntityTypes::WALL, &createWall}, {EntityTypes::BACKGROUND, &createBackground}};
            MapCall::const_iterator call;

            call = creator.find(entityType);
            if (call != creator.end()) {
                try {
                    UnpackVariadic::unpack.clear();
                    UnpackVariadic::unpackVariadicArgs(std::forward<Params>(args)...);
                    return (call->second(registry));
                } catch (const std::out_of_range &e)
                {
                    throw Exception("", "template <class... Params> static Registry &createEntity(Registry &registry, EntityTypes entityType, Params &&...args)");
                } catch (const std::bad_any_cast &e)
                {
                    throw Exception("", "template <class... Params> static Registry &createEntity(Registry &registry, EntityTypes entityType, Params &&...args)");
                }
            }
            throw ExceptionEntityUnobtainable("This entity doesn't exist", "Registry &Factory::createEntity(Registry &registry, EntityTypes entityType)");
        }

      private:
        static Entity createSpaceship(Registry &registry)
        {
            Entity entity = registry.spawnEntity();

            registry.addComponent<ecs::Drawable>(entity, ecs::Drawable());
            registry.addComponent<ecs::Collider>(entity, ecs::Collider());
            registry.addComponent<ecs::Controllable>(entity, ecs::Controllable());
            registry.addComponent<ecs::Killable>(entity, ecs::Killable());
            registry.addComponent<ecs::Shooter>(entity, ecs::Shooter());

            registry.addComponent<ecs::Position>(entity,
            ecs::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<ecs::Rectangle>(entity,
            ecs::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            registry.addComponent<ecs::Layer>(entity, ecs::Layer(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(6))));
            return (entity);
        }
        static Entity createMonster(Registry &registry)
        {
            Entity entity = registry.spawnEntity();

            registry.addComponent<ecs::Drawable>(entity, ecs::Drawable());
            registry.addComponent<ecs::Collider>(entity, ecs::Collider());
            registry.addComponent<ecs::Killable>(entity, ecs::Killable());

            registry.addComponent<ecs::Position>(entity,
            ecs::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<ecs::Rectangle>(entity,
            ecs::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            registry.addComponent<ecs::Layer>(entity, ecs::Layer(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(6))));
            return (entity);
        }
        static Entity createShot(Registry &registry)
        {
            Entity entity = registry.spawnEntity();

            registry.addComponent<ecs::Drawable>(entity, ecs::Drawable());
            registry.addComponent<ecs::Collider>(entity, ecs::Collider());

            registry.addComponent<ecs::Position>(entity,
            ecs::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<ecs::Rectangle>(entity,
            ecs::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            registry.addComponent<ecs::Layer>(entity, ecs::Layer(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(6))));

            registry.addComponent<ecs::Shootable>(entity, ecs::Shootable());
            return (entity);
        }
        static Entity createButton(Registry &registry)
        {
            Entity entity = registry.spawnEntity();

            registry.addComponent<ecs::Drawable>(entity, ecs::Drawable());
            registry.addComponent<ecs::Clickable>(entity, ecs::Clickable());

            registry.addComponent<ecs::Position>(entity,
            ecs::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<ecs::Rectangle>(entity,
            ecs::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            registry.addComponent<ecs::Layer>(entity, ecs::Layer(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(6))));
            return (entity);
        }
        static Entity createWall(Registry &registry)
        {
            Entity entity = registry.spawnEntity();

            registry.addComponent<ecs::Drawable>(entity, ecs::Drawable());
            registry.addComponent<ecs::Collider>(entity, ecs::Collider());

            registry.addComponent<ecs::Position>(entity,
            ecs::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<ecs::Rectangle>(entity,
            ecs::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            registry.addComponent<ecs::Layer>(entity, ecs::Layer(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(6))));
            return (entity);
        }
        static Entity createBackground(Registry &registry)
        {
            Entity entity = registry.spawnEntity();

            registry.addComponent<ecs::Drawable>(entity, ecs::Drawable());

            registry.addComponent<ecs::Position>(entity,
            ecs::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<ecs::Rectangle>(entity,
            ecs::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            registry.addComponent<ecs::Layer>(entity, ecs::Layer(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(6))));
            return (entity);
        }
    };
} // namespace ecs
