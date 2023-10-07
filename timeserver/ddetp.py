import socket

ip_server = "127.0.0.1"
port = 8080

SUCCESS = 0
ERR = 1


def createClientSocket():
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return client


def sendString(sockd,string):

    request = str.encode(string)
    sockd.sendto(request,(ip_server,port))

    res = sockd.recvfrom(1024)

    return res


def setnickname(sockd, nickname):
    
    return sendString(sockd,f"SETNICK {nickname}")

def goUp(sockd,nickname):

    return sendString(sockd,f"{nickname} UP")

def goDown(sockd,nickname):

    return sendString(sockd,f"{nickname} DOWN")


def exit(sockd,id):

    return sendString(sockd,f"EXIT {id}")

def assignRoom(sockd, nickname):
    
    return sendString(sockd,f"{nickname} ASSIGN")


def listen(sockd):

    return sockd.recvfrom(1024)






    

    


def createServerSocket():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(socket.gethostbyname(socket.gethostname()), constants.PORT)
    server.listen()
    return server

def receiveClient(server: socket.socket):
    connection, address = server.accept()
    return connection, address