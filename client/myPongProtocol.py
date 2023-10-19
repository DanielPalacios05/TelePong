# # echo-client.py

import socket


HOST = "54.221.21.98"  # The server's hostname or IP address
#HOST = "120.0.0.1"
PORT = 8081  # The port used by the server

def createSocket():
    client_socket  = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return client_socket

def createPlayer(nickname, client_socket, server_ip, port):
    f_nickname = str.encode("SERVER INIT_PLAYER " + nickname + "\0")
    client_socket.sendto(f_nickname,(server_ip, int(port)))

    player_number_bytes, _ = client_socket.recvfrom(1)
    game_id_bytes, _ = client_socket.recvfrom(1)

    playerNum = int.from_bytes(player_number_bytes, byteorder='big', signed=False)
    gameId = int.from_bytes(game_id_bytes, byteorder='big', signed=False)

    return playerNum, gameId

def sendMsg(msg, client_socket):
    f_msg = str.encode(msg + "\0")
    client_socket.sendto(f_msg ,(HOST,PORT))


def receiveOpponent(client_socket):

    opponent_nickname_bytes, _ = client_socket.recvfrom(15)
    opponent_nickname = opponent_nickname_bytes.decode('utf-8')
    opponent_nickname = opponent_nickname.replace("\0", "")
    print(opponent_nickname)

    return opponent_nickname

def sendAndReceiveMovement(client_socket, msg, server_ip, port):


    client_socket.settimeout(2)

    a = str.encode(msg+ "\0")
    #if movement != "NONE":
    print("Sent " + msg + " to the server")
    
    client_socket.sendto(a,(server_ip, int(port)))

    messageReceived = False
    while not messageReceived:
        try:
            opponent_move_bytes, _ = client_socket.recvfrom(4)
            messageReceived = True
        except TimeoutError:
            client_socket.sendto(a,(server_ip, int(port)))


    opponent_move = opponent_move_bytes.decode("utf-8")
    print("Received player move:"+ opponent_move)
    # Now you can use the player_number variable in your game logic
    return opponent_move

def sendWin(client_socket, msg, server_ip, port):


    client_socket.settimeout(1)

    a = str.encode(msg+ "\0")
    #if movement != "NONE":
    print("Sent " + msg + " to the server")
    
    client_socket.sendto(a,(server_ip, int(port)))

    messageReceived = False
    tries,maxtries = 0,2
    while not messageReceived and tries < maxtries:
        try:
            opponent_move_bytes, _ = client_socket.recvfrom(4)
            messageReceived = True
        except TimeoutError:
            client_socket.sendto(a,(server_ip, int(port)))
            tries+=1

    if tries == maxtries:
        return "NONE"


    opponent_move = opponent_move_bytes.decode("utf-8")
    print("Received player move:"+ opponent_move)
    # Now you can use the player_number variable in your game logic
    return opponent_move

def sendMovement(client_socket, msg, server_ip, port):


    client_socket.settimeout(2)

    a = str.encode(msg+ "\0")
    #if movement != "NONE":
    print("Sent " + msg + " to the server")
    client_socket.sendto(a,(server_ip, int(port)))
    # Now you can use the player_number variable in your game logic        

def handleCommunication(message, client_socket):
    seg_msg = message.split()
    if seg_msg[0] == 'PLAYER':
        if seg_msg[1] == 'CREATE_SOCKET':
            client_socket = createSocket()
            return client_socket
        if seg_msg[1] == 'CREATE_PLAYER':
            
            server_ip = seg_msg[2]
            port = seg_msg[3]
            nickname = seg_msg[4]
            playerNum, gameId = createPlayer(nickname, client_socket, server_ip, port)
            return playerNum, gameId
        if seg_msg[1] == 'RECEIVE_OPP':
            
            opp_nickname = receiveOpponent(client_socket)
            return opp_nickname
        if seg_msg[1] == 'SEND_MOVE':
            
            server_ip = seg_msg[2]
            port = seg_msg[3]
            msg = seg_msg[4] + " " + seg_msg[5] + " " + seg_msg[6] + " " + seg_msg[7] + " " + seg_msg[8]
            opp_movement = sendAndReceiveMovement(client_socket, msg, server_ip, port)
            return opp_movement
        
        if seg_msg[1] == 'SEND_WIN':
            
            server_ip = seg_msg[2]
            port = seg_msg[3]
            msg = seg_msg[4] + " " + seg_msg[5] + " " + seg_msg[6] + " " + seg_msg[7] + " " + seg_msg[8]
            opp_movement = sendWin(client_socket, msg, server_ip, port)
            return opp_movement
        
        if seg_msg[1] == 'SEND_CONF':
            
            server_ip = seg_msg[2]
            port = seg_msg[3]
            msg = seg_msg[4] + " " + seg_msg[5] + " " + seg_msg[6] + " " + seg_msg[7] + " " + seg_msg[8]
            opp_movement = sendMovement(client_socket, msg, server_ip, port)