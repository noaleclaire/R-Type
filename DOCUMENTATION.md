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



## Network

The server implements all the game logic. It acts as the authoritative source of game logic events in the
game.

-  1. UDP Protocol

    The first purpose of the R-Type UDP Protocol is to send all the frames to display (in the client) from the server to the client.

-   2. Asynchronous Protocol

    Asynchronous connectionless mode networking is conducted by configuring the endpoint for non-blocking service, and either polling for or receiving asynchronous notification when data might be transferred. If asynchronous notification is used, the actual receipt of data typically takes place within a signal handler.

- 3. Architecture Protocol

    ![citation Je t'aime - cadre sur ecran d'ordinateur et lignes de code](https://user-images.githubusercontent.com/72009611/196060225-b9e3677d-96e0-48c1-b260-ac18e4c899da.png)

- 4. Command Protocol
