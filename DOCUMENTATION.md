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
    
    ### SparseArray ECS
    
    A sparse set is a way of mapping sparse indexes to a tightly packed array. It essentially amounts to two lists, one sparsely filled with indexes to the     tightly packed list. And the packed list contains indexes back to the sparse list elements. A diagram might help this concept come across.
    
    ![sparsearray](https://user-images.githubusercontent.com/72009611/196367562-4c41aaa7-d2de-46e6-a514-d65cfc014ea4.png)
    


## Network

The server implements all the game logic. It acts as the authoritative source of game logic events in the
game.

-  1. UDP Protocol

    The first purpose of the R-Type UDP Protocol is to send all the frames to display (in the client) from the server to the client.

-  2. Asynchronous Protocol

    Asynchronous connectionless mode networking is conducted by configuring the endpoint for non-blocking service, and either polling for or receiving asynchronous notification when data might be transferred. If asynchronous notification is used, the actual receipt of data typically takes place within a signal handler.

- 3. Architecture Protocol
    
    ![netw](https://user-images.githubusercontent.com/72009611/196368292-df6a206d-1499-40ea-b447-62faeb331f53.png)
    
- 4. Command Protocol

    Use of serialisation: It lets you take an object or group of objects, put them on a disk or send them through a wire or wireless transport mechanism, then later, perhaps on another computer, reverse the process: resurrect the original object(s). The basic mechanisms are to flatten object(s) into a one-dimensional stream of bits, and to turn that stream of bits back into the original object(s).

    Format : Non-human-readable (“binary”) format

    Type of message send or receive:
    ```
    enum CustomMessage : uint32_t { 
        PingServer, 
        SwitchToGame, 
        SendGameComponent, 
        ComponentType, 
        AllGameComponentSent, 
        RemoveClient 
    };
    ```

## Display

Use of configurator file in yaml exemple : 

    ```
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
   ```


