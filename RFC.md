# RFC Documentation {#page_one}

## Introduction

The goal of the R-Type project is to create an online multiplayer copy of the classic R-Type game (1987).


## Features

- ECS
- Network with boost
- Configure file for sprite


## Network

The server implements all the game logic. It acts as the authoritative source of game logic events in the
game.
    
-  1. UDP Protocol


    The first purpose of the R-Type UDP Protocol is to send all the frames to display (in the client) from the server to the client.
    
    
    



