### RFC Documentation {#page_two}

The server implements all the game logic. It acts as the authoritative source of game logic events in the game.

## -  1. UDP Protocol

This User Datagram Protocol (UDP) is defined to make available a datagram mode of packet-switched computer communication in the environment of an interconnected set of computer networks.
This protocol provides  a procedure  for application  programs to send messages to other programs with a minimum of protocol mechanism.  
The first purpose of the R-Type UDP Protocol is to send all the frames to display (in the client) from the server to the client.

________________________________________________________________________________


## -  2. Asynchronous Protocol

Asynchronous connectionless mode networking is conducted by configuring the endpoint for non-blocking service, and either polling for or receiving asynchronous notification when data might be transferred. If asynchronous notification is used, the actual receipt of data typically takes place within a signal handler.


________________________________________________________________________________  


## - 3. Architecture Protocol
    
![netw](https://user-images.githubusercontent.com/72009611/196368292-df6a206d-1499-40ea-b447-62faeb331f53.png)


________________________________________________________________________________  


## - 4. Command Protocol

    Use of serialisation: It lets you take an object or group of objects, put them on a disk or send them through a wire or wireless transport mechanism, then later, perhaps on another computer, reverse the process: resurrect the original object(s). The basic mechanisms are to flatten object(s) into a one-dimensional stream of bits, and to turn that stream of bits back into the original object(s).

    Format : Non-human-readable (“binary”) format

###   - 1. Communications's basis
    
        PingServer :  
        This action is used to verify the connexion to a server

        RemoveClient :  
        This action is used to remove a client in a server

###    - 2. Entities management - Entity Creation

        SendComponent :   
        This action is used to send all components created in the server to the client

        AllComponentSent :  
        This action is used to setup information about components
    
###    - 3. Room management

        CreatePublicRoom :  
        This action is used to create a plublic room in a server

        CreatePrivateRoom :  
        This action is used to create a private room in a server

        InitListRoom :   
        This action is used to send all room avaible

        UpdateListRoom :  
        This action is used to update the room available in the client

        JoinRoomById :  
        This action is used to join a private room

        GetRoomScene :  
        This action is used to set the scene in the client
    
###    - 4. Error management

        MaxRoomLimit :  
        This action is used to notify the client that the maximum number of rooms have been created

        MaxPlayersInRoom :  
        This action is used to notify the client that the room cannot accept more clients

        RoomDoesntExists :  
        This action is used to notify the client that the room doesn't exist

