import socket

soc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

port = 11221
soc.bind(('',port))

while True:
	
	msg, addr = soc.recvfrom(1024)
	print("Connected to : ",addr)

	soc.sendto("Welcome to Server 102",addr)
	
	
