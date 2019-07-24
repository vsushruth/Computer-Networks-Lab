import socket

soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("Server created")

port = 11111
soc.bind(('',port))
print("Port reserved")

soc.listen(2)
print("Server Listening")

while True:
	
	c, addr = soc.accept()
	print("Connected to : ",addr)

	if(c.send("Welcome to Server 101")):
	
		c.close()
		break



