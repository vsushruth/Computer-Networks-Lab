import socket

soc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
print("Server socket created")

port = 11116
soc.bind(('',port))
print("Server binded to port")

msg = 'what'
while True:
	msg,addr = soc.recvfrom(1024)
	print("Connected to : ", addr)

	print(msg)
	while(msg != 'x'):
		soc.sendto(raw_input("Your message : "),addr)
		msg,addr = soc.recvfrom(1024)
		print(msg)
		if(msg == 'x'):
			print("\n Connection closed\n")
	
		
