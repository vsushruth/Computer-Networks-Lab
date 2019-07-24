import socket

c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
port = 11123
c.connect(('127.0.0.1', port))

msg = c.recv(1024)
print(msg)

c.send("DATE")
print(c.recv(1024))

c.close()
	
