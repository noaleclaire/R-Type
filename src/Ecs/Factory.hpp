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
            registry.addComponent<component::Collider>(entity, component::Collider());
            registry.addComponent<component::Controllable>(entity, component::Controllable());
            registry.addComponent<component::Drawable>(entity, component::Drawable());
            registry.addComponent<component::Killable>(entity, component::Killable());
            registry.addComponent<component::Position>(entity,
            component::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<component::Rectangle>(entity,
            component::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            registry.addComponent<component::Shooter>(entity, component::Shooter());
            return (entity);
        }
        static Entity createMonster(Registry &registry)
        {
            Entity entity = registry.spawnEntity();
            registry.addComponent<component::Collider>(entity, component::Collider());
            registry.addComponent<component::Drawable>(entity, component::Drawable());
            registry.addComponent<component::Killable>(entity, component::Killable());
            registry.addComponent<component::Position>(entity,
            component::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<component::Rectangle>(entity,
            component::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            return (entity);
        }
        static Entity createShot(Registry &registry)
        {
            Entity entity = registry.spawnEntity();
            registry.addComponent<component::Collider>(entity, component::Collider());
            registry.addComponent<component::Drawable>(entity, component::Drawable());
            registry.addComponent<component::Position>(entity,
            component::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<component::Rectangle>(entity,
            component::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            registry.addComponent<component::Shootable>(entity, component::Shootable());
            return (entity);
        }
        static Entity createButton(Registry &registry)
        {
            Entity entity = registry.spawnEntity();
            registry.addComponent<component::Clickable>(entity, component::Clickable());
            registry.addComponent<component::Drawable>(entity, component::Drawable());
            registry.addComponent<component::Position>(entity,
            component::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<component::Rectangle>(entity,
            component::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            return (entity);
        }
        static Entity createWall(Registry &registry)
        {
            Entity entity = registry.spawnEntity();
            registry.addComponent<component::Collider>(entity, component::Collider());
            registry.addComponent<component::Drawable>(entity, component::Drawable());
            registry.addComponent<component::Position>(entity,
            component::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<component::Rectangle>(entity,
            component::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            return (entity);
        }
        static Entity createBackground(Registry &registry)
        {
            Entity entity = registry.spawnEntity();
            registry.addComponent<component::Position>(entity,
            component::Position(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(0)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(1))));
            registry.addComponent<component::Rectangle>(entity,
            component::Rectangle(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(2)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(3)),
            UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(4)), UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(5))));
            registry.addComponent<component::Layer>(entity, component::Layer(UnpackVariadic::getArgNb(UnpackVariadic::unpack.at(6))));
            registry.addComponent<component::Drawable>(entity, component::Drawable());
            return (entity);
        }
    };
} // namespace ecs
