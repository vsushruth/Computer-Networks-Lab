import socket
from datetime import date

soc = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
print("Server socket created")

port = 11123
soc.bind(('',port))
print("Server binded to port")

soc.listen(1)
print("Server listening...")

while True:

	cli, addr = soc.accept()
	print("Connected to : ", addr)
	cli.send("Welcome to Server 101")

	if(cli.recv(1024) == "DATE"):
		cli.send(str(date.today()))
		break

	cli.close()	
	
