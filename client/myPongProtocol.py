# # echo-client.py

import socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 8080  # The port used by the server

def createSocket():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    return client_socket

def createPlayer(nickname, client_socket):
    f_nickname = str.encode(nickname)
    client_socket.sendto(f_nickname,(HOST,PORT))

    player_number_bytes, _ = client_socket.recvfrom(1)
    game_id_bytes, _ = client_socket.recvfrom(15)

    playerNum = int.from_bytes(player_number_bytes, byteorder='big', signed=False)
    gameId = int.from_bytes(game_id_bytes, byteorder='big', signed=False)

    return playerNum, gameId

def sendMsg(msg, client_socket):
    f_msg = str.encode(msg)
    client_socket.sendto(f_msg,(HOST,PORT))


def receiveOpponent(client_socket):

    opponent_nickname_bytes, _ = client_socket.recvfrom(15)
    opponent_nickname = opponent_nickname_bytes.decode('utf-8')
    opponent_nickname = opponent_nickname.replace("\0", "")

    return opponent_nickname

def sendMovement(client_socket, movement):
    a = str.encode(movement)
    #if movement != "NONE":
    #    print("Sent " + movement + " to the server")
    client_socket.sendto(a,(HOST,PORT))
    
    # In the client code where you receive data from the server
    player_number_bytes, _ = client_socket.recvfrom(1)
    player_number = int.from_bytes(player_number_bytes, byteorder='big')
    print("Received player number:", player_number)
    # Now you can use the player_number variable in your game logic

    receivedBytes = client_socket.recvfrom(1024)
    receivedmovement = receivedBytes[0].decode()
    #if receivedmovement != "NONE":
    #    print("Received " + receivedmovement + " from the server")
    return player_number, receivedmovement

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
        
    