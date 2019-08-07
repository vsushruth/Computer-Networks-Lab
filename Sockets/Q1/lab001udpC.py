import socket

cli = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

port = 11221
addr = ('127.0.0.1', port)

cli.sendto("Connecting to Server", addr)
print(cli.recvfrom(1024))

cli.close()

