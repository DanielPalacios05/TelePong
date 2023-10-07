import socket

ip_server = "127.0.0.1"
port = 8080


def createClientSocket():
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return client

def setnickname(sockd, nickname):
    
    request = str.encode(f"SETNICK {nickname}")

    sockd.sendto(request,(ip_server,port))

    res = sockd.recvfrom(1024)

    return res

    

    


def createServerSocket():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(socket.gethostbyname(socket.gethostname()), constants.PORT)
    server.listen()
    return server

def receiveClient(server: socket.socket):
    connection, address = server.accept()
    return connection, address