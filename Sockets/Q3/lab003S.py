import socket

soc = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
print("Server socket created")

port = 11115
soc.bind(('',port))
print("Server binded to port")

soc.listen(5)
print("Server listening for connection")

while True:

	cli,addr = soc.accept();
	print("Connected to ", addr);

	msg = cli.recv(1024)
	print(msg)
	while(msg != 'x'):
		sendM = raw_input("Your message : ")
		cli.send(sendM);
		msg = cli.recv(1024)
		print(msg)

	print("\nConnection closed\n")	
	cli.close()

