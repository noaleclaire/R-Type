/*
** EPITECH PROJECT, 2022
** Factory.cpp
** File description:
** Factory.cpp
*/

#include "Factory.hpp"
#include <functional>
#include <map>
#include "Component/component.hpp"
#include "Exceptions/ExceptionEntityUnobtainable.hpp"

namespace ecs
{
    typedef std::function<Registry &(Registry &)> fptr;
    typedef std::map<EntityTypes, fptr> MapCall;
    Registry &Factory::createEntity(Registry &registry, EntityTypes entityType)
    {
        MapCall creator = {{EntityTypes::SPACESHIP, &createSpaceship}, {EntityTypes::MONSTER, &createMonster}, {EntityTypes::SHOT, &createShot},
            {EntityTypes::BUTTON, &createButton}, {EntityTypes::WALL, &createWall}, {EntityTypes::BACKGROUND, &createBackground}};
        MapCall::const_iterator call;

        call = creator.find(entityType);
        if (call != creator.end())
            return (call->second(registry));
        throw ExceptionEntityUnobtainable("This entity doesn't exist", "Registry &Factory::createEntity(Registry &registry, EntityTypes entityType)");
    }

    Registry &Factory::createSpaceship(Registry &registry)
    {
        Entity entity = registry.spawnEntity();
        registry.addComponent<component::Collider>(entity, component::Collider());
        registry.addComponent<component::Controllable>(entity, component::Controllable());
        registry.addComponent<component::Drawable>(entity, component::Drawable());
        registry.addComponent<component::Killable>(entity, component::Killable());
        registry.addComponent<component::Position>(entity, component::Position(1, 1));
        registry.addComponent<component::Rectangle>(entity, component::Rectangle(1, 1, 1, 1));
        registry.addComponent<component::Shooter>(entity, component::Shooter());
        registry.addComponent<component::Velocity>(entity, component::Velocity(1, 1));
        return (registry);
    }

    Registry &Factory::createMonster(Registry &registry)
    {
        Entity entity = registry.spawnEntity();
        registry.addComponent<component::Collider>(entity, component::Collider());
        registry.addComponent<component::Drawable>(entity, component::Drawable());
        registry.addComponent<component::Killable>(entity, component::Killable());
        registry.addComponent<component::Position>(entity, component::Position(1, 1));
        registry.addComponent<component::Rectangle>(entity, component::Rectangle(1, 1, 1, 1));
        registry.addComponent<component::Velocity>(entity, component::Velocity(1, 1));
        return (registry);
    }

    Registry &Factory::createShot(Registry &registry)
    {
        Entity entity = registry.spawnEntity();
        // registry.addComponent<component::Collider>(entity, component::Collider());
        registry.addComponent<component::Drawable>(entity, component::Drawable());
        registry.addComponent<component::Position>(entity, component::Position(1, 1));
        registry.addComponent<component::Rectangle>(entity, component::Rectangle(1, 1, 1, 1));
        registry.addComponent<component::Shootable>(entity, component::Shootable(0));
        registry.addComponent<component::Velocity>(entity, component::Velocity(1, 1));
        return (registry);
    }

    Registry &Factory::createButton(Registry &registry)
    {
        Entity entity = registry.spawnEntity();
        // registry.addComponent<component::Clickable>(entity, component::Clickable());
        registry.addComponent<component::Drawable>(entity, component::Drawable());
        registry.addComponent<component::Position>(entity, component::Position(1, 1));
        registry.addComponent<component::Rectangle>(entity, component::Rectangle(1, 1, 1, 1));
        return (registry);
    }

    Registry &Factory::createWall(Registry &registry)
    {
        Entity entity = registry.spawnEntity();
        registry.addComponent<component::Collider>(entity, component::Collider());
        registry.addComponent<component::Drawable>(entity, component::Drawable());
        registry.addComponent<component::Position>(entity, component::Position(1, 1));
        registry.addComponent<component::Rectangle>(entity, component::Rectangle(1, 1, 1, 1));
        return (registry);
    }

    Registry &Factory::createBackground(Registry &registry)
    {
        Entity entity = registry.spawnEntity();
        registry.addComponent<component::Drawable>(entity, component::Drawable());
        registry.addComponent<component::Position>(entity, component::Position(1, 1));
        registry.addComponent<component::Rectangle>(entity, component::Rectangle(1, 1, 1, 1));
        return (registry);
    }
} // namespace ecs
