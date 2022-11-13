# Professional Documentation {#page_one}

## Introduction

The goal of the R-Type project is to create an online multiplayer copy of the classic R-Type game (1987).


## Features

- ECS
- Network with boost
- Configure file for sprite


## ECS

Entity Component System (ECS) is a software architectural pattern mostly used in video game development for the representation of game world objects. An ECS comprises entities composed from components of data, with systems which operate on entities' components.

- Entity: An entity represents a general-purpose object. In a game engine context, for example, every coarse game object is represented as an entity. Usually, it only consists of a unique id. Implementations typically use a plain integer for this.[1]

- Component: A component labels an entity as possessing a particular aspect, and holds the data needed to model that aspect. For example, every game object that can take damage might have a Health component associated with its entity. Implementations typically use structs, classes, or associative arrays.[1]

- System: A system is a process which acts on all entities with the desired components. For example a physics system may query for entities having mass, velocity and position components, and iterate over the results doing physics calculations on the sets of components for each entity.

    ### Architecture ECS

    ![ddddddd](https://user-images.githubusercontent.com/72009611/196061182-257c90ae-e8c9-4b25-94d4-ca4a653342c2.png)
    
    ### Entities
    An entity represents a general-purpose object. In a game engine context, for example, every coarse game object is represented as an entity. Usually, it     only consists of a unique id. Implementations typically use a plain integer for this.  
      
    The entitiy class:
    ```sh
    #include <iostream>
    #include <optional>

    namespace ecs {
        class Entity {
            explicit Entity(std::optional<std::size_t> id = std::nullopt);
            ~Entity();
            operator std::size_t();
            operator std::size_t() const;
            std::size_t getId() const;
            static std::size_t _idCount;
            private:
            std::size_t _id;
        };
    } 
    ```
    
    ### Component
    A component labels an entity as possessing a particular aspect, and holds the data needed to model that aspect. For example, every game object that can     take damage might have a Health component associated with its entity. Implementations typically use structs, classes, or associative arrays.    
     
     All components are base on a abstract class: 
     ```sh
     namespace ecs {
        class AComponent {
        public:
            AComponent() = default;
            ~AComponent() = default;
        };
    } 
     ```
     Exemple of component :
     ```sh
    #include "AComponent.hpp"
    namespace ecs
    {
        class Drawable : public AComponent {
            public:
            Drawable() = default;
            Drawable(const Drawable &other) = default;
            ~Drawable() = default;
            Drawable &operator=(const Drawable &other) = default;
        };
    } 
     ```
    
    ### Sytems
    A system is a process which acts on all entities with the desired components. For example a physics system may query for entities having mass, velocity     and position components, and iterate over the results doing physics calculations on the sets of components for each entity.  
    
    Exemple of system :  
    ```sh
     static void Drawable(Registry &registry, SparseArray<ecs::Drawable> const &drawable, graphics::Graphical *graphical);
    ```
     
    ### SparseArray ECS
    
    A sparse set is a way of mapping sparse indexes to a tightly packed array. It essentially amounts to two lists, one sparsely filled with indexes to the     tightly packed list. And the packed list contains indexes back to the sparse list elements. A diagram might help this concept come across.
    
    ![sparsearray](https://user-images.githubusercontent.com/72009611/196367562-4c41aaa7-d2de-46e6-a514-d65cfc014ea4.png)
    
    If you want see how it is created see the files :   
    src/ecs/component/SparseArray.hpp   
    src/ecs/Factory.hpp   
    src/ecs/Registry.hpp   

## Display and sprite manager

Use of configurator file in yaml exemple : 

    spritesheet: background.jpg
       background: 0
       anim: 0
       rect_x: 0
       rect_y: 0
       rect_width: 1280
       rect_height: 720 

    spritesheet: button.png
        button: 0
        anim: 0
        rect_x: 0
        rect_y: 0
        rect_width: 300
        rect_height: 110
    
   Use of sprite manager   


    class SpritesManager : public AYamlConfig {
    public:
        SpritesManager();
        ~SpritesManager();
        void executeMapMemberFunctionPointer(std::string &sprite_config_word, std::string &value);
        ecs::EntityTypes getSpriteType(std::string &sprite_type) const;
        std::string const getSpriteType(ecs::EntityTypes sprite_type) const;
        SpriteTypeAttributes getSpriteTypeAttribute(std::string &sprite_type_attribute) const;
        std::string const getSpriteTypeAttribute(SpriteTypeAttributes sprite_type_attribute) const;
        SpriteAnimAttributes getSpriteAnimAttribute(std::string &sprite_anim_attribute) const;
        std::string const getSpriteAnimAttribute(SpriteAnimAttributes sprite_anim_attribute) const;
        void addTexturePath(std::string &key_word, std::string &texture_path);
        void addSpriteTypeId(std::string &sprite_type, std::string &sprite_type_id);
        void addSpriteAnim(std::string &sprite_type_anim, std::string &sprite_type_anim_id);
        void addSpriteAnimAttributes(std::string &anim_attribute_type, std::string &anim_attribute_value);
        std::vector<std::string> const getTexturePath() const;
        std::vector<float> get_Animations_rect(ecs::EntityTypes entity_type, std::size_t entity_id, std::size_t anim_id = 0);
        int getNbAnimation(ecs::EntityTypes entity_type, std::size_t entity_id, std::size_t anim_id = 0);
        int getSpeedAnimation(ecs::EntityTypes entity_type, std::size_t entity_id, std::size_t anim_id = 0);
        int getNextAnimation(ecs::EntityTypes entity_type, std::size_t entity_id, std::size_t anim_id = 0);
        float getAnimationCurrentFrame(ecs::EntityTypes entity_type, std::size_t entity_id);
        void setAnimationCurrentFrame(ecs::EntityTypes entity_type, std::size_t entity_id, float increm);
        int getIndexCurrentAnimation(ecs::EntityTypes entity_type, std::size_t entity_id);
        void setIndexCurrentAnimation(ecs::EntityTypes entity_type, std::size_t entity_id, int index);
        std::string get_Spritesheet(ecs::EntityTypes entity_type, std::size_t entity_id);
        void printSpritesData();
    }

## Exemple of creation : 
A background
    
    std::vector<float> rect;
    std::size_t entity;
    rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
            
A button

    rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 6, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 280, 173, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 6, 4);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 6), rect);

  


