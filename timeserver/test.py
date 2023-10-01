import ddetp



sock = ddetp.createClientSocket()

while True:

    a = input("nickname: ")

    ret = ddetp.setnickname(sock, a)


    ddetp.assignRoom(sock,a)
    ddetp.goDown(sock,a)
    ddetp.goUp(sock,a)
    print(ret[0],ret[1])