# # echo-client.py

import socket


#HOST = "127.0.0.1"  # The server's hostname or IP address
HOST = "18.215.165.27"
PORT = 8080  # The port used by the server

def createSocket():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    return client_socket

def createPlayer(nickname, client_socket):
    f_nickname = str.encode("SERVER INIT_PLAYER " + nickname + "\0")
    client_socket.sendto(f_nickname,(HOST,PORT))

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

    return opponent_nickname

def sendAndReceiveMovement(client_socket, msg):
    a = str.encode(msg+ "\0")
    #if movement != "NONE":
    print("Sent " + msg + " to the server")
    
    client_socket.sendto(a,(HOST,PORT))
    
    # In the client code where you receive data from the server
    opponent_move_bytes, _ = client_socket.recvfrom(4)
    opponent_move = opponent_move_bytes.decode("utf-8")
    print("Received player move:"+ opponent_move)
    # Now you can use the player_number variable in your game logic
    #if receivedmovement != "NONE":
    #    print("Received " + receivedmovement + " from the server")
    return opponent_move

#     return receiveddata

# def sendMovement(client_socket, movement):
#     a = str.encode(movement)
#     client_socket.sendto(a, (HOST, PORT))

#     # Wait for the server's response (acknowledgment)
#     receivedBytes, server_address = client_socket.recvfrom(1024)
#     receiveddata = receivedBytes.decode()

#     return receiveddata

# with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:

#     while True:
#        a = str.encode(input("say sum: "))
#        s.sendto(a,(HOST,PORT))

#        receivedBytes = s.recvfrom(1024)
#        print(receivedBytes[0].decode())
        
    