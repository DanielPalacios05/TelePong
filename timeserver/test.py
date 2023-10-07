import ddetp



sock = ddetp.createClientSocket()

while True:

    a = input("nickname: ")

    ret = ddetp.setnickname(sock, a);

    print(ret[0],ret[1])