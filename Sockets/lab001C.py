import socket

c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
port = 11111

c.connect(('218.248.46.107', port))

print(c.recv(1024))

c.close()
