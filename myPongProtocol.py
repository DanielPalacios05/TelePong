import socket
import constants

def createClientSocket():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    return client

def createServerSocket():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(socket.gethostbyname(socket.gethostname()), constants.PORT)
    server.listen()
    return server

def receiveClient(server: socket.socket):
    connection, address = server.accept()
    return connection, address

