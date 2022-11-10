# RFC Documentation {#page_one}

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
    
    PingServer
    This action is used to verify the connexion to a server

    RemoveClient
    This action is used to remove a client in a server

    AllComponentSent
    This action is used to send all components created in the server to the client

    CreatePublicRoom
    This action is used to create a plublic room in a server

    CreatePrivateRoom
    This action is used to create a private room in a server

    InitListRoom
    This action is used to send all room avaible

    JoinRoomById
    This action is used to join a private room
    
    MaxRoomLimit
    This action is used to notify the client that the maximum number of rooms have been created

    MaxPlayersInRoom
    This action is used to notify the client that the room cannot accept more clients

    RoomDoesntExists
    This action is used to notify the client that the room doesn't exist