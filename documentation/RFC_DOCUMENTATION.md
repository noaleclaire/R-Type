### RFC Documentation {#page_two}

The server implements all the game logic. It acts as the authoritative source of game logic events in the game.

## -  1. UDP Protocol

This User Datagram Protocol (UDP) is defined to make available a datagram mode of packet-switched computer communication in the environment of an interconnected set of computer networks.
This protocol provides  a procedure  for application  programs to send messages to other programs with a minimum of protocol mechanism.  
The first purpose of the R-Type UDP Protocol is to send all the frames to display (in the client) from the server to the client.

________________________________________________________________________________


## -  2. Asynchronous Protocol

Asynchronous connectionless mode networking is conducted by configuring the endpoint for non-blocking service, and either polling for or receiving asynchronous notification when data might be transferred. If asynchronous notification is used, the actual receipt of data typically takes place within a signal handler.

Senders function :
       

        void writeHeaderStrand(shared_session const &session) 
        {
            _socket.async_send_to(boost::asio::buffer(&session->_send_msg.header, sizeof(Header<T>)), session->_remote_endpoint, _strand.wrap(boost::bind(
            &UdpSession<T>::handleSentWriteHeader, session, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
        }
        void writeBodyStrand(shared_session const &session) 
        {
            _socket.async_send_to(boost::asio::buffer(session->_send_msg.body.data(), session->_send_msg.body.size()), session->_remote_endpoint, _strand.wrap(boost::bind(&UdpSession<T>::handleSentWriteBody, session, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
        }  

Receiver function :

        void readHeader()
        {
            auto session = std::make_shared<UdpSession<T>>(this);

            _socket.async_receive_from(boost::asio::buffer(&session->_recv_msg.header, sizeof(Header<T>)), session->_remote_endpoint,
                _strand.wrap(boost::bind(
                    &UdpServerClient::handleReceiveReadHeader, this, session, boost::asio::placeholders::error,             boost::asio::placeholders::bytes_transferred)));
        }
        void readBody(shared_session const &session)
        {
            _socket.async_receive_from(boost::asio::buffer(session->_recv_msg.body.data(), session->_recv_msg.body.size()), session->_remote_endpoint,
                _strand.wrap(boost::bind(
                    &UdpServerClient::handleReceiveReadBody, this, session, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
            readHeader();
        }

________________________________________________________________________________  


## - 3. Architecture Protocol
    
![netw](https://user-images.githubusercontent.com/72009611/196368292-df6a206d-1499-40ea-b447-62faeb331f53.png)


________________________________________________________________________________  


## - 4. Command Protocol

    Use of serialisation: It lets you take an object or group of objects, put them on a disk or send them through a wire or wireless transport mechanism, then later, perhaps on another computer, reverse the process: resurrect the original object(s). The basic mechanisms are to flatten object(s) into a one-dimensional stream of bits, and to turn that stream of bits back into the original object(s).

    Format : Non-human-readable (“binary”) format
    
    Enum message:  

    enum CustomMessage : uint32_t { PingServer, PingClient,
                                CreatePublicRoom, CreatePrivateRoom, MaxRoomLimit,
                                GetScene,
                                InitListRoom, UpdateListRoom,
                                JoinRoom, JoinRoomById, MaxPlayersInRoom, RoomDoesntExists,
                                SwitchRoomMode, IsHost,
                                QuitRoomServer, QuitRoomClient,
                                SendComponent, AllComponentSent,
                                SwitchToGame, InitGame, KillAnEntity,
                                RemoveClient, NotEnoughPlayer, CreateShot,
                                UpdatePosPlayerServer, UpdatePosPlayerClient };

###   - 1. Communications's basis
    
        PingServer :  
        This action is used to verify the connexion to a server
        
        PingCLient :  
        This action is used to verify the connexion to a server

        RemoveClient :  
        This action is used to remove a client in a server

###    - 2. Entities management - Entity Creation

        SendComponent :   
        This action is used to send all components created in the server to the client

        AllComponentSent :  
        This action is used to setup information about components
        
        KillAnEntity :
        This action is used to destroy an entity

###    - 3. Scene
        
        GetScene :
        This action is used to send the scene to the client
    
###    - 4. Room management

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
        
        JoinRoom :
        This action is used to join a private room  
    
        GetRoomScene :  
        This action is used to set the scene in the client
        
        SwitchRoomMode:
        This action is used to set the mode in the room in the server
        
        SwitchToGame :
        This action is used to lauch the game in the client
        
        IsHost :
        This action is used to set the host of a game in the server
        
        QuitRoomServer :
        This action is used to quit a server
        
        QuitRoomClient :
        This action is used to destroy a room in the client side

###    - 5. Game

        InitGame :
        This action is used to launch all component use in the gameplay
        
        CreateShot :
        This action is used to use shot in the client
        
        UpdatePosPlayerServer :
        This action is used to set and update the player position in the server
        
        UpdatePosPlayerClient :
        This action is used to set and update the player position in the client
    
###    - 6. Error management

        MaxRoomLimit :  
        This action is used to notify the client that the maximum number of rooms have been created

        MaxPlayersInRoom :  
        This action is used to notify the client that the room cannot accept more clients

        RoomDoesntExists :  
        This action is used to notify the client that the room doesn't exist

