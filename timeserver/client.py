# echo-client.py

import socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 8080  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:

    while True:
        a = str.encode(input("say sum: "))
        s.sendto(a,(HOST,PORT))

        receivedBytes = s.recvfrom(1024);
        print(receivedBytes[0].decode())
1

        
    
